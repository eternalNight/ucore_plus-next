#ifndef _LINUX_FTRACE_H
#define _LINUX_FTRACE_H

/*
 * taken from include/linux/ftrace.h
 */

#include <proc.h>

#ifdef UCONFIG_FTRACE

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
 * Structure that defines a return function trace.
 */
struct ftrace_graph_ret {
	unsigned long func; /* Current function */
	unsigned long long calltime;
	unsigned long long rettime;
	/* Number of functions that overran the depth limit for current task */
	unsigned long overrun;
	int depth;
};

extern int function_trace_stop;

#define FTRACE_RETFUNC_DEPTH 50
#define FTRACE_RETSTACK_ALLOC_SIZE 32
/* Type of the callback handlers for tracing function graph*/
typedef void (*trace_func_graph_ret_t)(struct ftrace_graph_ret *); /* return     */
typedef int (*trace_func_graph_ent_t)(struct ftrace_graph_ent *); /* entry *    /


 /*
 * Primary handler of a function return.
 * It relays on ftrace_return_to_handler.
 * Defined in entry_32/64.S
 */
extern void return_to_handler(void);

extern void ftrace_stub(unsigned long a0, unsigned long a1);

extern int ftrace_push_return_trace(unsigned long ret, unsigned long func,
		int *depth, unsigned long frame_pointer);

extern void ftrace_graph_init_task(struct proc_struct *t);
extern void ftrace_graph_exit_task(struct proc_struct *t);
//extern void ftrace_graph_init_idle_task(struct proc_struct *t, int cpu); // TODO_LTY: needed for idle proc?

#endif /* UCONFIG_FTRACE */

#endif /* _LINUX_FTRACE_H */
