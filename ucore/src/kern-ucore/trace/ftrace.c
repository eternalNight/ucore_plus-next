/*
 * taken from kernel/trace/ftrace.c
 */

#include <linux/ftrace.h>
#include <slab.h>
#include <atomic.h>

static int ftrace_graph_active;

static void graph_init_task(struct proc_struct *t,
		struct ftrace_ret_stack *ret_stack) {
	atomic_set(&t->tracing_graph_pause, 0);
	atomic_set(&t->trace_overrun, 0);
	t->ftrace_timestamp = 0;
	/* make curr_ret_stack visable before we add the ret_stack */

	/* TODO_LTY: needed for multicore?
	 * smp_wmb();
	 */
	t->ret_stack = ret_stack;
}

/* Allocate a return stack for newly created task */
void ftrace_graph_init_task(struct proc_struct *t) {
	/* Make sure we do not use the parent ret_stack */
	t->ret_stack = NULL;
	t->curr_ret_stack = -1;

	if (ftrace_graph_active) {
		struct ftrace_ret_stack *ret_stack;

		ret_stack = kmalloc(
				FTRACE_RETFUNC_DEPTH * sizeof(struct ftrace_ret_stack));
		if (!ret_stack)
			return;
		graph_init_task(t, ret_stack);
	}
}

void ftrace_graph_exit_task(struct proc_struct *t) {
	struct ftrace_ret_stack *ret_stack = t->ret_stack;

	t->ret_stack = NULL;
	/* NULL must become visible to IRQs before we free it: */
	barrier();

	kfree(ret_stack);
}

