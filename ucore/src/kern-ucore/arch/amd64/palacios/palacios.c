#include "palacios.h"

#include "test_blob.h"
// #include "test_blob2.h"
// #include "test_blob_dos4.h"
// #include "test_blob_msdos.h"
// #include "test_blob_linux.h"
// #include "test_blob_kitten.h"
// #include "test_blob_freedos2.h"

#include <types.h>
#include <pmm.h>
#include <sem.h>
#include <proc.h>
#include <stdarg.h>
#include <stdio.h>
#include <slab.h>
#include <sched.h>
#include <picirq.h>
#include <x86.h>

static struct v3_vm_info * g_vm_guest = NULL;
static struct v3_vm_info * irq_to_guest_map[256];
static uintptr_t guest_iso_start;
static size_t guest_iso_size;

void send_key_to_palacios(unsigned char status, unsigned char scan_code)
{
// TODO: comment two rows below?
	if (!g_vm_guest)
		return;

	struct v3_keyboard_event event = {
		.status    = status,
		.scan_code = scan_code,
	};

	v3_deliver_keyboard_event(g_vm_guest, &event);
}
void send_mouse_to_palacios(unsigned char packet[3])
{
	if (!g_vm_guest)
		return;

	struct v3_mouse_event event;
	memcpy(event.data, packet, 3);

	v3_deliver_mouse_event(g_vm_guest, &event);
}
void send_tick_to_palacios(unsigned int period_us)
{
	if (!g_vm_guest)
		return;

	struct v3_timer_event event = {
		.period_us = period_us,
	};

	v3_deliver_timer_event(g_vm_guest, &event);
}

static void palacios_print(const char * fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vkprintf(fmt, ap);
	va_end(ap);
}

static void * palacios_allocate_pages(int num_pages, unsigned int alignment)
{
	struct Page * p = alloc_pages(num_pages);
	if (p == NULL) {	// TODO:
		return NULL;
	}
	return (void *)page2pa(p);
}

static void palacios_free_pages(void * page_paddr, int num_pages)
{
	struct Page * p = pa2page((uintptr_t)page_paddr);
	free_pages(p, num_pages);
}

static void * palacios_malloc(unsigned int size)
{
	return kmalloc(size);
}

static void palacios_free(void * addr)
{
	return kfree(addr);
}

static void * palacios_paddr_to_vaddr(void * paddr)
{
	return (void *)KADDR(paddr);
}

static void * palacios_vaddr_to_paddr(void * vaddr)
{
	return (void *)PADDR(vaddr);
}

// 
void translate_intr_handler(struct trapframe *state)
{
	
	struct v3_interrupt intr;

	intr.irq = state->tf_trapno - 32; 
	intr.error = state->tf_err;
	intr.should_ack = 0;

	//  PrintBoth("translate_intr_handler: opaque=0x%x\n",mystate.opaque);
	v3_deliver_irq(irq_to_guest_map[intr.irq], &intr);
	//End_IRQ(state);
	int irq = state->tf_trapno - 32;
	unsigned char command = 0x60 | (irq & 0x7);
	
	if (irq < 8) 
	{
		outb(0x20, command);
	}   
	else 
	{
		outb(0xA0, command);
		outb(0x20, 0x62);
	}   
	
}

/* instructs the kernel to forward the specified IRQ to palacios */
static int palacios_hook_interrupt(struct v3_vm_info *	vm,	unsigned int vector)
{
	
	if (irq_to_guest_map[vector]) {
		vkprintf("%s: Interrupt vector %u is already hooked.\n",
		       __func__, vector);
		return -1;
	}

	vkprintf("%s: Hooking interrupt vector %u to vm %p.\n",
	       __func__, vector, vm);

	irq_to_guest_map[vector] = vm;

	install_IRQ(vector, translate_intr_handler);
	
	pic_enable(vector);

	return 0;
}

/* acknowledges an interrupt */
static int palacios_ack_interrupt(int vector)
{
	int irq = vector;
	unsigned char command = 0x60 | (irq & 0x7);
	
	if (irq < 8) 
	{
		outb(0x20, command);
	}   
	else 
	{
		outb(0xA0, command);
		outb(0x20, 0x62);
	}   
	//		lapic_ack_interrupt();
	return 0;
}

static unsigned int palacios_get_cpu_khz(void)
{
	// TODO
	return 2000000;
}

/* yield the CPU so other Host OS tasks can run */
static void palacios_yield_cpu(void)
{
	// TODO
	schedule();
}

static void * palacios_mutex_alloc(void)
{
	semaphore_t * sem = kmalloc(sizeof(semaphore_t));
	if (sem)
		sem_init(sem, 1);
	return (void *)sem;
}

static void palacios_mutex_free(void * mutex)
{
	kfree(mutex);
}

static void palacios_mutex_lock(void * mutex, int must_spin)
{
	down((semaphore_t *)mutex);
}

static void palacios_mutex_unlock(void * mutex)
{
	up((semaphore_t *)mutex);
}

static unsigned int palacios_get_cpu(void)
{
	// TODO
	return 0;
}

/* creates a kernel thread */
static void * palacios_start_kernel_thread(int (*fn)(void *arg), void * arg, char * thread_name)
{
	// TODO
	int pid = kernel_thread(fn, arg, 0);
	if (pid < 0) {
		return NULL;
	}
	struct proc_struct * ps = find_proc(pid);
	if (ps != NULL) {
		set_proc_name(ps, thread_name);
	}
	return (void *)ps;
}

/* interrupt the physical CPU corresponding to the specified logical guest CPU */
static void palacios_interrupt_cpu(struct v3_vm_info * vm, int cpu_id, int vector)
{
	vkprintf("Faking interruption of target CPU by not doing anything since there is only one CPU\n");
}

/* runs a function on the specified CPU */
static void palacios_xcall(int cpu_id, void (*fn)(void *arg), void * arg)
{
	fn(arg);
}

/* starts a kernel thread on the specified CPU */
static void * palacios_start_thread_on_cpu(int cpu_id, int (*fn)(void * arg), void * arg, char * thread_name)
{
	// TODO
	int pid = kernel_thread(fn, arg, 0);
	if (pid < 0) {
		return NULL;
	}
	struct proc_struct * ps = find_proc(pid);
	if (ps != NULL) {
		set_proc_name(ps, thread_name);
	}
	return (void *)ps;
}


struct v3_os_hooks palacios_os_hooks = {
	.print = palacios_print,					// ok
	.allocate_pages = palacios_allocate_pages,	//
	.free_pages = palacios_free_pages,			//
	.malloc = palacios_malloc,					//
	.free = palacios_free,						//
	.paddr_to_vaddr = palacios_paddr_to_vaddr,	//
	.vaddr_to_paddr = palacios_vaddr_to_paddr,	//
	.hook_interrupt = palacios_hook_interrupt,
	.ack_irq = palacios_ack_interrupt,
	.get_cpu_khz = palacios_get_cpu_khz,	// ok
	.yield_cpu = palacios_yield_cpu,		
	.mutex_alloc = palacios_mutex_alloc,	//
	.mutex_free = palacios_mutex_free,		//
	.mutex_lock = palacios_mutex_lock,		//
	.mutex_unlock = palacios_mutex_unlock,	//
	.get_cpu = palacios_get_cpu,			//
	.start_kernel_thread = palacios_start_kernel_thread,
	.interrupt_cpu = palacios_interrupt_cpu,
	.call_on_cpu = palacios_xcall,
	.start_thread_on_cpu = palacios_start_thread_on_cpu,
};

#define IRQ_NONE 0
#define IRQ_HANDLED 1
/**
 * Direct keyboard interrupts to the Palacios hypervisor.
 */
static int
palacios_keyboard_interrupt(
	int			vector,
	void *			unused
)
{
	const uint8_t KB_STATUS_PORT = 0x64;
	const uint8_t KB_DATA_PORT   = 0x60;
	const uint8_t KB_OUTPUT_FULL = 0x01;

	uint8_t status = inb(KB_STATUS_PORT);

	if ((status & KB_OUTPUT_FULL) == 0)
		return IRQ_NONE;

	uint8_t key = inb(KB_DATA_PORT);
	send_key_to_palacios(status, key);

	return IRQ_HANDLED;
}

int palacios_init(void * a)
{
	vkprintf("Starting to init palacios...\n");
	Init_V3(&palacios_os_hooks, 1);
	vkprintf("After init palacios...\n");
	install_IRQ(1, palacios_keyboard_interrupt);
	RunVMM();
	return 0;
}

int RunVMM() 
{
	vkprintf("step1\n");
	vkprintf("1. load img to memory\n");
	char *vaddr = myblob;
	if(vaddr == NULL)
	{
		vkprintf("Array created failed\n");
		return -1;
	}
	guest_iso_start = PADDR(vaddr);
	
	
	vkprintf("2. create a vm\n");
	struct v3_vm_info * vm_info = v3_create_vm((void *)KADDR(guest_iso_start), NULL, NULL);
	if(vm_info == NULL)
	{
		vkprintf("VM creatation failed\n");
		if(vaddr) kfree(vaddr);
		return -1;
	}
	g_vm_guest = vm_info;

	vkprintf("3. Starting a guest OS...\n");
	v3_start_vm(vm_info, 1);
	
	vkprintf("End of RunVMM\n");
	return 0;
}
