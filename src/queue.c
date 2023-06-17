#include "../lib/queue.h"
#include "../lib/process.h"
#include <stdlib.h>
#include <stdio.h>

#define do_prints 0


/*

QUEUE STRUCTURE (Use monospaced font for optimal viewing experience)

Queue Head (original queue object) -> Queue object -> Queue object -> ... -> Queue tail (oldest object)
                                    ^                                               ^
                                    |                                               |
            New queue objects are added here with queue_add()     The queue tail can be queue_peek()ed or queue_poll()ed

*/


int queue_add(void* new_object, queue_object* queue){
    // Attempt to prevent segmentation faults by checking for null pointers here
    if (new_object == NULL) {
        fprintf(stderr, "\n[QUEUE/FATAL] Cannot create a queue with a NULL object pointer!\n");
        return 1;
    }
    if (queue == NULL) {
        fprintf(stderr, "\n[QUEUE/FATAL] Cannot create a queue with a NULL queue pointer!\n");
        return 1;
    }

    queue_object* temp = new_queue(); // Create new queue handler
    temp->object = new_object;
    temp->next = queue->next; // Copy current first object pointer
    queue->next = temp; // Insert as first object
    if (do_prints) 
    {
        printf("\n[QUEUE] Added %.1s successfully!\n", queue->next->object);
    }
    return 0;
}

void* queue_poll(queue_object* queue){
    if (queue->next == NULL) { // Check if the queue has any items
        if (do_prints){
            printf("\n[QUEUE] Polling on an empty queue!\n");
        }
        return NULL;
    }

    queue_object* current_q_obj = queue;

    queue_object* next_queue_object = current_q_obj->next;

    while (next_queue_object->next != NULL) { // Find object that points to last object
        current_q_obj = next_queue_object;
        next_queue_object = current_q_obj->next;
    }
    
    void* last_object = next_queue_object->object;

    free(next_queue_object);
    current_q_obj->next = NULL;
    
    if (do_prints) {
        printf("\n[QUEUE] Successfully polled %.1s!\n", last_object);
    }

    return last_object;
}

queue_object* new_queue(){
    queue_object* q = (queue_object*) malloc(sizeof(queue_object));
    q->next = NULL; // Initialise these to prevent uncontrolled conditional jumps
    q->object = NULL; // (They appeared in valgrind beforehand)
    return q;
}


void free_queue(queue_object* queue){
    int free_counter = 1; // because feedback is nice
    while (queue->next != NULL) {
        queue_poll(queue);
        free_counter++;
    }

    if (do_prints) {
        printf("\n[QUEUE] Successfully freed %i queue object(s)!\n", free_counter);
    }

    free(queue);
}

void* queue_peek(queue_object* queue){
    queue_object* current_q_obj = queue;
    if (queue->next == NULL) { // Check if the queue has any items
        if (do_prints) {
            printf("\n[QUEUE] Peeking on an empty queue!\n");
        }
        return NULL;
    }

    queue_object* next_queue_object = queue->next;

    while (next_queue_object != NULL) { // Keep going until null pointer
        current_q_obj = next_queue_object;
        next_queue_object = current_q_obj->next;
    }

    if (do_prints) {
        printf("\n[QUEUE] Successfully peeked %.1s!\n", current_q_obj->object);
    }

    return current_q_obj->object;
}

void print_queue(queue_object* queue){ // Print a queue. Assumes queue->object is a process* pointer
    printf("\n[QUEUE] Current queue: ");
    queue_object* current_q_obj = queue;
    int i = 0;
    while (current_q_obj->next != NULL) {
        current_q_obj = current_q_obj->next;
        process* obj = (process*) current_q_obj->object;
        if (obj == NULL) {
            fprintf(stderr, "\n[QUEUE/FATAL] Illegally encountered NULL object!\n");
            exit(1);
        }
        else {
            printf(" %c ", obj->id);
        }
        i++;
    }

    printf(" Length: %i", i);

    printf("\n");
}
