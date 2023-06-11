#include"../lib/scheduler.h"
#include"../lib/process.h"
#include "helpers.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   7
#define RR_QUANTUM      2
#define STRATEGY        SJN

int main()
{
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{   0,      3,      1,      'A'},
                                        {   1,      2,      4,      'B'},
                                        {   4,      1,      2,      'C'},
                                        {   2,      5,      3,      'D'},
                                        {   7,      1,      5,      'E'},
                                        {   3,      8,      2,      'F'},
                                        {   5,      3,      7,      'G'}};
    char* expected_result = "AAABBCGGGEDDDDDFFFFFFFF";
    print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);

    unsigned int err = compare_result(resulting_schedule, expected_result);
    free(resulting_schedule);
    exit(err);
}
