#include"../lib/scheduler.h"
#include"../lib/process.h"
#include "helpers.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   10
#define RR_QUANTUM      2
#define STRATEGY        RR

int main()
{
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{   0,      3,      1,      'A'},
                                        {   1,      3,      4,      'B'},
                                        {   2,      3,      2,      'C'},
                                        {   3,      3,      6,      'D'},
                                        {   4,      3,      2,      'E'},
                                        {   5,      3,      10,     'F'},
                                        {   6,      3,      2,      'G'},
                                        {   7,      3,      2,      'H'},
                                        {   8,      3,      2,      'I'},
                                        {   9,      3,      2,      'J'}};
    char* expected_result = "AABBCCADDEEBFFGGCHHIIJJDEFGHIJ";
    print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);

    unsigned int err = compare_result(resulting_schedule, expected_result);
    free(resulting_schedule);
    exit(err);
}
