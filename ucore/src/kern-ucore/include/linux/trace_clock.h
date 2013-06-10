/*
 * taken from include/linux/trace_clock.h
 */

#ifndef _LINUX_TRACE_CLOCK_H
#define _LINUX_TRACE_CLOCK_H

#include <linux/compiler.h>

extern unsigned long long notrace trace_clock_local(void);

#endif /* _LINUX_TRACE_CLOCK_H */

