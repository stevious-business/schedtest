#include"../lib/scheduler.h"
#include"../lib/process.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include "helpers.h"

#define PROCESS_COUNT   6
#define RR_QUANTUM      2
#define STRATEGY        FCFS

int main()
{
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{   0,      3,      1,      'A'},
                                        {   2,      2,      3,      'B'},
                                        {   3,      1,      2,      'C'},
                                        {   4,      3,      5,      'D'},
                                        {   5,      2,      4,      'E'},
                                        {  12,      2,      2,      'F'}};
    char* expected_result = "AAABBCDDDEE FF";
    print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);

    unsigned int err = compare_result(resulting_schedule, expected_result);
    free(resulting_schedule);
    exit(err);
}
