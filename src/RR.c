#include "../lib/RR.h"

#define do_prints 0

static queue_object* RR_queue;
static int global_quantum;
static int quantum_tick; // What tick of the quantum are we currently on?

process* RR_tick (process* running_process){

    if (running_process == NULL) {
        running_process = queue_poll(RR_queue);
        if (running_process != NULL) {
            quantum_tick = global_quantum;
        }
    }
    else if (running_process->time_left == 0) {
        quantum_tick = global_quantum;
        running_process = queue_poll(RR_queue);
    }
    else if (quantum_tick == 0) {
        quantum_tick = global_quantum;
        if (running_process != NULL) { // Only re-append current process if it exists
            if (queue_add(running_process, RR_queue)) {
                exit(1); // error occurred
            }
        }
        running_process = queue_poll(RR_queue);
    }

    if (running_process!=NULL){
        running_process->time_left--;
    }

    quantum_tick--;

    return running_process;
}

int RR_startup(int quantum){
    quantum_tick = quantum;
    global_quantum = quantum;
    RR_queue = new_queue();
    return 0;
}


process* RR_new_arrival(process* arriving_process, process* running_process){
    if (arriving_process == NULL) {
        return running_process;
    }
    if (running_process == NULL) {
        running_process = arriving_process;
        quantum_tick = global_quantum;
    }
    else {
        if (queue_add(arriving_process, RR_queue)) {
            exit(1); // error occurred
        }
    }

    return running_process;
}


void RR_finish(){
    free_queue(RR_queue);
}
