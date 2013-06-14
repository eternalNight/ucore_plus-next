#include <kio.h>

void test_ftrace_enter_0() {
	static int i = 0;
	kprintf("enter mcount: %d\n", i);
	i++;
}

