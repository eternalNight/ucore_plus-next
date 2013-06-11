#ifndef _LINUX_FTRACE_H
#define _LINUX_FTRACE_H

/*
 * taken from include/linux/ftrace.h
 */

#include <proc.h>

#ifdef UCONFIG_FTRACE

#define FTRACE_RETFUNC_DEPTH 50

/*
 * Structure that defines an entry function trace.
 */
struct ftrace_graph_ent {
	unsigned long func; /* Current function */
	int depth;
};

/*
 * Stack of return addresses for functions
 * of a thread.
 * Used in struct thread_info
 */
struct ftrace_ret_stack {
	unsigned long ret;
	unsigned long func;
	unsigned long long calltime;
	unsigned long long subtime;
	unsigned long fp;
};

/*
 * Primary handler of a function return.
 * It relays on ftrace_return_to_handler.
 * Defined in entry_32/64.S
 */
extern void return_to_handler(void);

extern int ftrace_push_return_trace(unsigned long ret, unsigned long func,
		int *depth, unsigned long frame_pointer);

extern void ftrace_graph_init_task(struct proc_struct *t);
extern void ftrace_graph_exit_task(struct proc_struct *t);

#endif /* UCONFIG_FTRACE */

#endif /* _LINUX_FTRACE_H */
