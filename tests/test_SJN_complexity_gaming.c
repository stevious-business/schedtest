#include"../lib/scheduler.h"
#include"../lib/process.h"
#include "helpers.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   6
#define RR_QUANTUM      2
#define STRATEGY        SJN

int main()
{
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{   0,      5,      1,      'A'},
                                        {   1,      2,      4,      'B'},
                                        {   3,      1,      2,      'C'},
                                        {   4,      4,      6,      'D'},
                                        {   6,      7,      2,      'E'},
                                        {   10,     2,      10,     'F'}};
    char* expected_result = "AAAAACBBDDDDFFEEEEEEE";
    print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);

    unsigned int err = compare_result(resulting_schedule, expected_result);
    free(resulting_schedule);
    exit(err);
}
