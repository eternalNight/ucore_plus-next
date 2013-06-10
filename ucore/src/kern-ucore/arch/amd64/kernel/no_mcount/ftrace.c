/*
 * taken from arch/x86/kernel/ftrace.c
 */

#include <linux/ftrace.h>

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

	trace.func = self_addr;

	*parent = old; //TODO_LTY remove

}

