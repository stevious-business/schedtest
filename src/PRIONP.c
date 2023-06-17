#include "../lib/PRIONP.h"
#include <stdio.h>

static queue_object* PRIONP_queue;
//You can add more global variables here

static process* find_next(queue_object* queue) {
    unsigned int highest_prio = 0; // Ratio value
    queue_object* highest_prio_proc = NULL; // The actual highest-prio process
    queue_object* before_hp_proc = NULL; // Process before the highest-prio process
    queue_object* current_q_obj = queue; // Iterates through the q(ueue)
    queue_object* last_q_obj = queue; // The process where proc->next is current_q_obj
    process* next_process = NULL; // The finally returned value (which is stored before free())

    while (current_q_obj->next != NULL) { // Go until end of queue
        last_q_obj = current_q_obj;
        current_q_obj = current_q_obj->next;
        if (((process*) current_q_obj->object)->priority >= highest_prio) {
            highest_prio = ((process*) current_q_obj->object)->priority;
            highest_prio_proc = current_q_obj;
            before_hp_proc = last_q_obj;
        }
    }
    if (highest_prio_proc == NULL) {
        return NULL;
    }

    before_hp_proc->next = highest_prio_proc->next;
    next_process = (process*) highest_prio_proc->object;

    free(highest_prio_proc);

    return next_process;
}

process* PRIONP_tick (process* running_process){
    if (running_process == NULL) { // Get a new process to run
        running_process = find_next(PRIONP_queue);
    }
    else {
        if (running_process->time_left == 0) {
            running_process = find_next(PRIONP_queue);
        }
    }
    if (running_process != NULL) {
        running_process->time_left--;
    }
    return running_process;
}

int PRIONP_startup(){
    PRIONP_queue = new_queue();
    return 0;
}

process* PRIONP_new_arrival(process* arriving_process, process* running_process){
    if (running_process == NULL) {
        running_process = arriving_process;
    }
    else if (arriving_process != NULL) {
        queue_add(arriving_process, PRIONP_queue);
    }
    return running_process;
}

void PRIONP_finish(){
    free(PRIONP_queue);
}
