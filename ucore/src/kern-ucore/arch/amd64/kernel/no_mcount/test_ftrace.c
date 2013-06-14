#include <kio.h>

void test_ftrace_enter_0() {
	static int i = 0;
	if (i % 100 == 0) {
		kprintf("enter mcount: %d\n", i);
		i = 0;
	}
	i++;
}

void test_ftrace_exit_0() {
	static int i = 0;
	if (i % 100 == 0) {
		kprintf("exit mcount: %d\n", i);
		i = 0;
	}
	i++;
}

