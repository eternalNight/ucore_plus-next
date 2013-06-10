/*
 * taken from arch/x86/include/asm/linkage.h
 */

#ifndef _ASM_X86_LINKAGE_H
#define _ASM_X86_LINKAGE_H

#undef notrace
#define notrace __attribute__((no_instrument_function))

#ifdef __ASSEMBLY__

#define GLOBAL(name)	\
	.globl name;	\
	name:

#endif /* __ASSEMBLY__  */

#endif /* _ASM_X86_LINKAGE_H */

