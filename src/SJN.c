#include "../lib/SJN.h"
#include "stdio.h"

static queue_object* SJN_queue;
//You can add more global variables here

static process* find_next(queue_object* queue) {
    uint shortest_job_time = 4294967295; // Assume longest possible duration
    queue_object* shortest_job_proc = NULL; // The actually shortest process
    queue_object* before_shortest_proc = NULL; // Process before the shortest proc.
    queue_object* current_q_obj = queue; // Iterates through the q(ueue)
    queue_object* last_q_obj = queue; // The process where proc->next is current_q_obj
    process* next_process = NULL; // The finally returned value (which is stored before free())

    while (current_q_obj->next != NULL) { // Go until end of queue
        last_q_obj = current_q_obj;
        current_q_obj = current_q_obj->next;
        if (((process*) current_q_obj->object)->time_left <= shortest_job_time) {
            shortest_job_time = ((process*) current_q_obj->object)->time_left;
            shortest_job_proc = current_q_obj;
            before_shortest_proc = last_q_obj;
        }
    }
    if (shortest_job_proc == NULL) {
        //printf("\n[SJN] Returning Null\n");
        return NULL;
    }

    before_shortest_proc->next = shortest_job_proc->next;
    next_process = (process*) shortest_job_proc->object;

    free(shortest_job_proc);

    return next_process;
}

process* SJN_tick (process* running_process){
    if (running_process == NULL) { // Get a new process to run
        running_process = find_next(SJN_queue);
    }
    else {
        if (running_process->time_left == 0) {
            running_process = find_next(SJN_queue);
        }
    }
    if (running_process != NULL) {
        running_process->time_left--;
    }
    return running_process;
}

int SJN_startup(){
    SJN_queue = new_queue();
    return 0;
}

process* SJN_new_arrival(process* arriving_process, process* running_process){
    if (running_process == NULL) {
        running_process = arriving_process;
    }
    else if (arriving_process != NULL) {
        queue_add(arriving_process, SJN_queue);
    }
    return running_process;
}

void SJN_finish(){
    free(SJN_queue);
}
