/*
 * taken from arch/x86/kernel/tsc.c
 */

#include <asm/timer.h>

/*
 * Scheduler clock - returns current time in nanosec units.
 */
unsigned long long native_sched_clock(void) {
	unsigned long long this_offset;

	/*
	 * Fall back to jiffies if there's no TSC available:
	 * ( But note that we still use it if the TSC is marked
	 *   unstable. We do this because unlike Time Of Day,
	 *   the scheduler clock tolerates small errors and it's
	 *   very important for it to be as fast as the platform
	 *   can achieve it. )
	 */

	/* read the Time Stamp Counter: */
	rdtscll(this_offset);

	/* return the value in ns */
	return __cycles_2_ns(this_offset);

	//TODO_LTY: implement this
}
