#include "../lib/MLF.h"
#include <stdio.h>

#define NQUEUES 4 // Number of queues

static queue_object** MLF_queues;
static int quanta[NQUEUES] = {1, 2, 6, -1}; // quanta for every level (-1/infinite for the final queue)
static int quantum_tick; // Which tick of the quantum are we on
static int running_queue; // Which queue is running_process in

process* MLF_tick (process* running_process){
    int proc_done = 0; // We have to check for nullptrs, so an extra variable is necessary
    if (running_process != NULL) {
        proc_done = running_process->time_left <= 0; // Check whether existing process is done
    }
    if (quantum_tick == 0 || running_process == NULL || proc_done) { // Condition for finding a new process
        if (running_process != NULL) {
            if (running_process->time_left > 0) {
                // Move the currently running process to the next queue
                queue_add(running_process, MLF_queues[running_queue+1>=NQUEUES ? NQUEUES-1 : running_queue+1]);
            }
        }
        running_process = NULL; // In case all queues are empty, we must return null
        for (int i=0; i<NQUEUES;i++) { // Iterate through all queues until we find one that's not empty
            if (MLF_queues[i]->next != NULL) { // Check for the first queue that has items
                running_queue = i; // Our new running process queue
                running_process = queue_poll(MLF_queues[i]); // Get the actual new running process
                quantum_tick = quanta[i]; // Set the quantum
                break;
            }
        }
    }
    if (running_process != NULL) { // Cannot use "else" due to potential change of running_process
        running_process->time_left--;
    }
    quantum_tick--; // Reduce the time left in the quantum (Does nothing for FCFS, as quantum_tick is initialised negatively there)
    return running_process;
}

int MLF_startup(){
    // Initialise variables
    quantum_tick = quanta[0];
    running_queue = 0;
    // Allocate space for queues
    MLF_queues = malloc(sizeof(queue_object*)*NQUEUES);
    if (MLF_queues == NULL) { // Error checking
        fprintf(stderr, "\n[MLF/FATAL] Failed to malloc() MLF queue array!\n");
        return 1;
    }
    for (int i=0; i<NQUEUES; i++) {
        MLF_queues[i] = new_queue();
        if (MLF_queues[i] == NULL) { // Error checking
            fprintf(stderr, "\n[MLF/FATAL] Failed to malloc() an MLF queue!\n");
            return 1;
        }
    }
    return 0;
}

process* MLF_new_arrival(process* arriving_process, process* running_process){
    if (arriving_process == NULL) {
        return running_process;
    }
    if (running_process == NULL) { // No active process -> run the arriving process
        running_process = arriving_process;
        running_queue = 0;
        quantum_tick = quanta[0];
    }
    else {
        if (queue_add(arriving_process, MLF_queues[0])) { // Otherwise add to the first queue
            fprintf(stderr, "\n[MLF/FATAL] Failed to add object to queue!\n");
            exit(1);
        };
    }
    return running_process;
}

void MLF_finish(){
    // Free MLF queues
    for (int i=0; i<NQUEUES; i++) {
        free_queue(MLF_queues[i]);
    }
    free(MLF_queues);
}
