#include <kio.h>

void test_ftrace_0_enter() {
	static int i = 0;
	kprintf("enter mcount: %d\n", i);
	i++;
}

