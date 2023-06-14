#include"../lib/scheduler.h"
#include"../lib/process.h"
#include "helpers.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   10
#define RR_QUANTUM      2
#define STRATEGY        PRIONP

int main()
{
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{   0,      2,      1,      'A'},
                                        {   1,      2,      4,      'B'},
                                        {   2,      2,      2,      'C'},
                                        {   3,      2,      6,      'D'},
                                        {   4,      2,      3,      'E'},
                                        {   5,      2,      10,     'F'},
                                        {   6,      2,      12,      'G'},
                                        {   7,      2,      8,      'H'},
                                        {   8,      2,      4,      'I'},
                                        {   9,      2,      2,      'J'}};
    char* expected_result = "AABBDDGGFFHHIIEECCJJ";
    print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);

    unsigned int err = compare_result(resulting_schedule, expected_result);
    free(resulting_schedule);
    exit(err);
}
