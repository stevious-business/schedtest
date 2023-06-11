#ifndef SCHEDULER_HELPERS_H
#define SCHEDULER_HELPERS_H

#include "../lib/process.h"
#include "../lib/scheduler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline const char * strategy_str(scheduling_strategy s) {
	switch(s) {
	case FCFS: return "FCFS";
	case LCFSPR: return "LCFSPR";
	case HRRN: return "HRRN";
	case MLF: return "MLF";
	case PRIONP: return "PRIONP";
	case RR: return "RR";
	case SJN: return "SJN";
	default: return "Unknown";
	}
}

static inline void print_schedule_info(
	size_t count,
	scheduling_strategy s,
	int quantum,
	process * procs) {

	printf("Process count: %zu\n", count);
	printf("Strategy     : %s\n", strategy_str(s));
	if(quantum) {
		printf("Quantum      : %d\n", quantum);
	}

	printf("+---------------------------------------+\n");
	printf("| ID | Start Time | Duration | Priority |\n");
	printf("+---------------------------------------+\n");
	for(size_t i = 0; i < count; i++) {
		printf("|%3c |%11u |%9u |%9u |\n",
			procs[i].id,
			procs[i].start_time,
			procs[i].time_left,
			procs[i].priority
		);
	}
	printf("+---------------------------------------+\n");
}

static inline unsigned int compare_result(char * result, char * expected) {
	printf("Result\n------\nGot     : %s\nExpected: %s\n", result, expected);

	if(strcmp(result, expected)) {
		printf("Did not match!\n");
		return 1;
	} else {
		printf("Matches\n");
		return 0;
	}
}

#endif
