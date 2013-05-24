#include <kio.h>

void test_ftrace_0() {
	static int i = 0;
	kprintf("in mcount: %d\n", i);
	i++;
}

