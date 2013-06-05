#ifndef _LINUX_LINKAGE_H
#define _LINUX_LINKAGE_H

/*
 * taken from include/linux/linkage.h
 */

/*
 * #ifdef __ASSEMBLY__ is not used here
 */

#ifndef __ALIGN
#define __ALIGN		.align 4,0x90
#define __ALIGN_STR	".align 4,0x90"
#endif

#ifndef LINKER_SCRIPT

#define ALIGN __ALIGN

#ifndef ENTRY
#define ENTRY(name) \
  .globl name; \
  ALIGN; \
  name:
#endif

#ifndef END
#define END(name) \
  .size name, .-name
#endif

#endif /* LINKER_SCRIPT */

#endif /* _LINUX_LINKAGE_H */

