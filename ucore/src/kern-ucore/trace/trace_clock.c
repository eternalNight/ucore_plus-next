/*
 * take from kernel/trace/trace_clock.c
 */

#include <linux/trace_clock.h>

/*
 * trace_clock_local(): the simplest and least coherent tracing clock.
 *
 * Useful for tracing that does not cross to other CPUs nor
 * does it go through idle events.
 */
unsigned long long notrace trace_clock_local(void) {
	//unsigned long long clock;

	/*
	 * sched_clock() is an architecture implemented, fast, scalable,
	 * lockless clock. It is not guaranteed to be coherent across
	 * CPUs, nor across CPU idle events.
	 */
	/*
	 * int resched;
	 * resched = ftrace_preempt_disable();
	 */
	//clock = sched_clock();
	//TODO_LTY: sched_clock will be implemented later
	/*
	 * ftrace_preempt_enable(resched);
	 */
	/*
	 * TODO_LTY: preempt sched in ucore?
	 */

	// temporary hack
	// similar to arch/x86/include/asm/msr.h
	unsigned low, high; // DECLARE_ARGS(val, low, high)

	//asm volatile("rdtsc" : EAX_EDX_RET(val, low, high));
	asm volatile("rdtsc" : "=a" (low), "=d" (high));

	return ((low) | ((unsigned long long) (high) << 32)); // EAX_EDX_VAL(val, low, high)

	//return clock;
}

