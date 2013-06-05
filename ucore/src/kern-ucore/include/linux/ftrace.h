#ifndef _LINUX_FTRACE_H
#define _LINUX_FTRACE_H

/*
 * taken from include/linux/ftrace.h
 */

#ifdef UCONFIG_FTRACE

/*
 * Primary handler of a function return.
 * It relays on ftrace_return_to_handler.
 * Defined in entry_32/64.S
 */
extern void return_to_handler(void);

#endif /* UCONFIG_FTRACE */

#endif /* _LINUX_FTRACE_H */
