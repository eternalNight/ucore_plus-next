#include <mmu.h>
#include <memlayout.h>
#include <linux/linkage.h>
#include <asm/linkage.h>

#ifdef UCONFIG_FTRACE
#include <asm/ftrace.h>
#endif /* UCONFIG_FTRACE */

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

# TODO_LTY: use ENTRY END as in include/linux/linkage.h

ENTRY(mcount)
    MCOUNT_SAVE_FRAME

    call test_ftrace_0_enter

    MCOUNT_RESTORE_FRAME
    retq
END(mcount)

.global return_to_handler
return_to_handler:


#endif /* UCONFIG_FTRACE */

.data
.align PGSIZE
    .globl bootstack
bootstack:
    .space KSTACKSIZE
    .globl bootstacktop
bootstacktop:


