#include <mmu.h>
#include <memlayout.h>

.text
.code64
.global kern_entry64
kern_entry64:
    movq $0x0, %rbp
    movq $KERNBASE, %rsp
    addq $bootstacktop - KERNBASE, %rsp
    call kern_init

# should never get here
spin:
    jmp spin

.global kern_ap_entry64
kern_ap_entry64:
    movq $0x0, %rbp
#rsp already setup
    call ap_init
    jmp spin

#ifdef UCONFIG_FTRACE

# TODO: use ENTRY END as in include/linux/linkage.h

.global mcount
mcount:
    call test_ftrace_0
    ret

#endif

.data
.align PGSIZE
    .globl bootstack
bootstack:
    .space KSTACKSIZE
    .globl bootstacktop
bootstacktop:


