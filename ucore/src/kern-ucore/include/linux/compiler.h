/*
 * taken from include/linux/compiler.h
 */

#ifndef __LINUX_COMPILER_H
#define __LINUX_COMPILER_H

#ifndef __ASSEMBLY__

#define notrace __attribute__((no_instrument_function))

#endif /* __ASSEMBLY__ */

#endif /* __LINUX_COMPILER_H */
