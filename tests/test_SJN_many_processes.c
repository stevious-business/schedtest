#include"../lib/scheduler.h"
#include"../lib/process.h"
#include "helpers.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   10
#define RR_QUANTUM      2
#define STRATEGY        SJN

int main()
{
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{   0,      2,      1,      'A'},
                                        {   2,      3,      4,      'B'},
                                        {   3,      2,      2,      'C'},
                                        {   4,      7,      6,      'D'},
                                        {   5,      5,      2,      'E'},
                                        {   7,      2,      10,     'F'},
                                        {   8,      3,      2,      'G'},
                                        {   10,      6,      2,      'H'},
                                        {   11,      8,      8,      'I'},
                                        {   12,      2,      2,      'J'}};
    char* expected_result = "AABBBCCFFGGGJJEEEEEHHHHHHDDDDDDDIIIIIIII";
    print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);

    unsigned int err = compare_result(resulting_schedule, expected_result);
    free(resulting_schedule);
    exit(err);
}
