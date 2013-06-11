/*
 * taken from kernel/trace/ftrace.c
 */

#include <linux/ftrace.h>

static int ftrace_graph_active;

/* Allocate a return stack for newly created task */
void ftrace_graph_init_task(struct proc_struct *t) {
	/* Make sure we do not use the parent ret_stack */
	t->ret_stack = NULL;
	t->curr_ret_stack = -1;

	if (ftrace_graph_active) {
		struct ftrace_ret_stack *ret_stack;

		ret_stack = kmalloc(
				FTRACE_RETFUNC_DEPTH * sizeof(struct ftrace_ret_stack),
				GFP_KERNEL);
		if (!ret_stack)
			return;
		graph_init_task(t, ret_stack);
	}
}

