/*
 * taken from arch/x86/kernel/ftrace.c
 */

#include <linux/ftrace.h>

void prepare_ftrace_return(unsigned long *parent, unsigned long self_addr,
		unsigned long frame_pointer) {
	unsigned long old;
	unsigned long return_hooker = (unsigned long) &return_to_handler;

}

