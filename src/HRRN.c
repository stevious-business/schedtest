#include "../lib/HRRN.h"

static queue_object* HRRN_queue;
static unsigned int global_tick; // ticks since the start of the system
//You can add more global variables and structs here

static process* find_next(queue_object* queue) {
    double highest_ratio = 0.0; // Ratio value
    double ratio = 0.0; // Individually calculated
    queue_object* highest_ratio_proc = NULL; // The actual HRR process
    queue_object* before_hr_proc = NULL; // Process before the HRR process
    queue_object* current_q_obj = queue; // Iterates through the q(ueue)
    queue_object* last_q_obj = queue; // The process where proc->next is current_q_obj
    process* next_process = NULL; // The finally returned value (which is stored before free())

    while (current_q_obj->next != NULL) { // Go until end of queue
        last_q_obj = current_q_obj;
        current_q_obj = current_q_obj->next;
        int service_time = ((process*) current_q_obj->object)->time_left;
        ratio = (service_time+(global_tick-((process*) current_q_obj->object)->start_time))/service_time;
        if (ratio > highest_ratio) {
            highest_ratio = ratio;
            highest_ratio_proc = current_q_obj;
            before_hr_proc = last_q_obj;
        }
    }
    if (highest_ratio_proc == NULL) {
        return NULL;
    }

    before_hr_proc->next = highest_ratio_proc->next;
    next_process = (process*) highest_ratio_proc->object;

    free(highest_ratio_proc);

    return next_process;
}

process* HRRN_tick (process* running_process){
    if (running_process == NULL) { // Get a new process to run
        running_process = find_next(HRRN_queue);
    }
    else {
        if (running_process->time_left == 0) {
            running_process = find_next(HRRN_queue);
        }
    }
    if (running_process != NULL) {
        running_process->time_left--;
    }
    global_tick++;
    return running_process;
}

int HRRN_startup(){
    HRRN_queue = new_queue();
    global_tick = 0;
    return 0;
}

process* HRRN_new_arrival(process* arriving_process, process* running_process){
    if (running_process == NULL) {
        running_process = arriving_process;
    }
    else if (arriving_process != NULL) {
        queue_add(arriving_process, HRRN_queue);
    }
    return running_process;
}

void HRRN_finish(){
    free_queue(HRRN_queue);
}
