#include"../lib/scheduler.h"
#include"../lib/process.h"
#include "helpers.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   10
#define RR_QUANTUM      2
#define STRATEGY        LCFSPR

int main()
{
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{   0,      2,      1,      'A'},
                                        {   1,      5,      4,      'B'},
                                        {   2,      4,      2,      'C'},
                                        {   3,      2,      3,      'D'},
                                        {   4,      1,      2,      'E'},
                                        {   5,      2,      10,     'F'},
                                        {   6,      2,      2,      'G'},
                                        {   7,      2,      2,      'H'},
                                        {   8,      2,      2,      'I'},
                                        {   9,      2,      2,      'J'}};
    char* expected_result = "ABCDEFGHIJJABBBBCCCDFGHI";
    print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);

    unsigned int err = compare_result(resulting_schedule, expected_result);
    free(resulting_schedule);
    exit(err);
}
