/*
 * taken from kernel/trace/trace_functions_graph.c
 */

#include <linux/ftrace.h>

#include <asm/ftrace.h>

unsigned long ftrace_return_to_handler(unsigned long frame_pointer) {
	unsigned long ret;
	return ret;
}

/* Add a function return address to the trace stack on thread info.*/
int ftrace_push_return_trace(unsigned long ret, unsigned long func, int *depth,
		unsigned long frame_pointer) {

	unsigned long long calltime;
	int index;

	if (!current->ret_stack)
		return -EBUSY;

	/*
	 * We must make sure the ret_stack is tested before we read
	 * anything else.
	 */
	/*
	 * smp_rmb();
	 * TODO_LTY: smp_rmb probably needed with multi-core
	 */

	/* The return trace stack is full */
	if (current->curr_ret_stack == FTRACE_RETFUNC_DEPTH - 1) {
		atomic_inc(&current->trace_overrun);
		return -EBUSY;
	}

	//calltime = trace_clock_local();

	index = ++current->curr_ret_stack;
	barrier();
	current->ret_stack[index].ret = ret;
	current->ret_stack[index].func = func;
	current->ret_stack[index].calltime = calltime;
	current->ret_stack[index].subtime = 0;
	current->ret_stack[index].fp = frame_pointer;
	*depth = index;

	return 0;
}
