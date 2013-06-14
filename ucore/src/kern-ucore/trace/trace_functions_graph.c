/*
 * taken from kernel/trace/trace_functions_graph.c
 */

#include <linux/ftrace.h>
#include <error.h>
#include <arch.h>
#include <asm/ftrace.h>

// TODO_LTY: remove
#include <test_ftrace.h>

/* Retrieve a function return address to the trace stack on thread info.*/
static void ftrace_pop_return_trace(struct ftrace_graph_ret *trace,
		unsigned long *ret, unsigned long frame_pointer) {
	int index;

	index = current->curr_ret_stack;

	/*
	 * removed panic code - lty
	 */

	/*
	 * CONFIG_HAVE_FUNCTION_GRAPH_FP_TEST removed - lty
	 */

	*ret = current->ret_stack[index].ret;
	trace->func = current->ret_stack[index].func;
	trace->calltime = current->ret_stack[index].calltime;
	trace->overrun = atomic_read(&current->trace_overrun);
	trace->depth = index;
}

unsigned long ftrace_return_to_handler(unsigned long frame_pointer) {
	struct ftrace_graph_ret trace;
	unsigned long ret;

	/*
	 * removed panic code - lty
	 */

	ftrace_pop_return_trace(&trace, &ret, frame_pointer);
	trace.rettime = trace_clock_local();
	//ftrace_graph_return(&trace); TODO_LTY
	test_ftrace_exit_0();
	barrier();
	current->curr_ret_stack--;

	return ret;
}

/* Add a function return address to the trace stack on thread info.*/
int ftrace_push_return_trace(unsigned long ret, unsigned long func, int *depth,
		unsigned long frame_pointer) {

	unsigned long long calltime;
	int index;

	if (!current->ret_stack)
		return -E_BUSY;

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
		return -E_BUSY;
	}

	calltime = trace_clock_local();

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

