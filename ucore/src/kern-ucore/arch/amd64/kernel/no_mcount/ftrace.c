/*
 * taken from arch/x86/kernel/ftrace.c
 */

#include <linux/ftrace.h>
#include <error.h>

void prepare_ftrace_return(unsigned long *parent, unsigned long self_addr,
		unsigned long frame_pointer) {

	unsigned long old;
	unsigned long return_hooker = (unsigned long) &return_to_handler;

	/*
	 * TODO: handle fault as in linux
	 */

	asm volatile(
			"movq (%[parent]), %[old]\n"
			"movq %[return_hooker], (%[parent])\n"

			: [old] "=&r" (old)
			: [parent] "r" (parent), [return_hooker] "r" (return_hooker)
			: "memory"
	);

	struct ftrace_graph_ent trace;

	if (ftrace_push_return_trace(old, self_addr, &trace.depth,
			frame_pointer) == -E_BUSY) {*
		parent = old;
		return;
	}

	trace.func = self_addr;

	/* Only trace if the calling function expects to */
	/*
	 if (!ftrace_graph_entry(&trace)) {
	 current->curr_ret_stack--;
	 *parent = old;
	 }
	 */

}

