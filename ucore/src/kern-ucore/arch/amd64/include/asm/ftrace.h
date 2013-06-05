#ifndef _ASM_X86_FTRACE_H
#define _ASM_X86_FTRACE_H

/*
 * taken from linux 2.6.34.14
 *
 * arch/x86/include/asm/ftrace.h
 */

 /*
 * #ifdef __ASSEMBLY__ is not used here
 */

.macro MCOUNT_SAVE_FRAME
/* taken from glibc */
subq $0x38, %rsp
movq %rax, (%rsp)
movq %rcx, 8(%rsp)
movq %rdx, 16(%rsp)
movq %rsi, 24(%rsp)
movq %rdi, 32(%rsp)
movq %r8, 40(%rsp)
movq %r9, 48(%rsp)
.endm

.macro MCOUNT_RESTORE_FRAME
movq 48(%rsp), %r9
movq 40(%rsp), %r8
movq 32(%rsp), %rdi
movq 24(%rsp), %rsi
movq 16(%rsp), %rdx
movq 8(%rsp), %rcx
movq (%rsp), %rax
addq $0x38, %rsp
.endm

#ifdef UCONFIG_FTRACE

#define MCOUNT_INSN_SIZE    5 /* sizeof mcount call */

#endif /* UCONFIG_FTRACE */

#endif /* _ASM_X86_FTRACE_H */
