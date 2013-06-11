#include <mmu.h>
#include <memlayout.h>
#include <linux/linkage.h>
#include <asm/linkage.h>
#include <asm/ftrace.h>

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

/*
 * implement CONFIG_FUNCTION_GRAPH_TRACER in linux
 *
 * taken from arch/x86/kernel/entry_64.S
 */

ENTRY(mcount)
    jmp ftrace_graph_caller
END(mcount)

ENTRY(ftrace_graph_caller)
    MCOUNT_SAVE_FRAME

    leaq 8(%rbp), %rdi
    movq 0x38(%rsp), %rsi
    movq (%rbp), %rdx
    subq $MCOUNT_INSN_SIZE, %rsi

    call    prepare_ftrace_return

    MCOUNT_RESTORE_FRAME

    retq
END(ftrace_graph_caller)

GLOBAL(return_to_handler)
    subq  $24, %rsp

    /* Save the return values */
    movq %rax, (%rsp)
    movq %rdx, 8(%rsp)
    movq %rbp, %rdi

    call ftrace_return_to_handler

    movq %rax, %rdi
    movq 8(%rsp), %rdx
    movq (%rsp), %rax
    addq $24, %rsp
    jmp *%rdi

#endif /* UCONFIG_FTRACE */

.data
.align PGSIZE
    .globl bootstack
bootstack:
    .space KSTACKSIZE
    .globl bootstacktop
bootstacktop:


