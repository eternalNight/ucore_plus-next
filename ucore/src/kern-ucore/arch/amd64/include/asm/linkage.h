#ifndef _ASM_X86_LINKAGE_H
#define _ASM_X86_LINKAGE_H

/*
 * taken from arch/x86/include/asm/linkage.h
 */

/*
 * #ifdef __ASSEMBLY__ is not used here
 */

#define GLOBAL(name)	\
	.globl name;	\
	name:

#endif /* _ASM_X86_LINKAGE_H */
