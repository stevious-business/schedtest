#include "../lib/LCFSPR.h"

static queue_object* LCFSPR_queue;
//You can add more global variables here

int LCFSPR_startup(){
    LCFSPR_queue = new_queue();
    return 0;
}

process* LCFSPR_tick (process* running_process){
    if (running_process == NULL) {
        running_process = queue_poll(LCFSPR_queue);
    }
    else {
        if (running_process->time_left == 0) {
            running_process = queue_poll(LCFSPR_queue);
        }
    }
    if (running_process != NULL) {
        running_process->time_left--;
    }
    return running_process;
}


process* LCFSPR_new_arrival(process* arriving_process, process* running_process){
    if (arriving_process == NULL) {
        return running_process;
    }
    if (running_process != NULL) {
        if (running_process->time_left == 0) {
            return arriving_process;
        }
        queue_add(running_process, LCFSPR_queue);
    }
    return arriving_process;
}

void LCFSPR_finish(){
    free_queue(LCFSPR_queue);
}
