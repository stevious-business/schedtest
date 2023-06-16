#include "../lib/queue.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

int main(){
	char * letter_A = malloc(sizeof(char));
	if(letter_A == NULL){
		fprintf(stderr, "malloc returned NULL. Unexpected!\n");
		exit(1);
	}
	*letter_A = 'A';

	printf("Creating new queue\n");
	queue_object *queue = new_queue();
	if(queue == NULL) {
		fprintf(stderr, "Expected non NULL value for freshly create queu\n");
		exit(1);
	}

	printf("Adding A to queue\n");
	if(queue_add(letter_A, queue)){
		fprintf(stderr, "Adding an element to the queue returned and error\n");
		exit(1);
	}

	printf("Peeking queue\n");
	char *peek = queue_peek(queue);
	if(peek == NULL){
		fprintf(stderr, "Expected peek to return a valid pointer but got NULL\n");
		exit(1);
	} else if(peek != letter_A){
		fprintf(stderr, "Expected %p, but got %p\n", letter_A, peek);
		exit(1);
	} else if(*peek != 'A'){
		fprintf(stderr, "Content was modified. Expected A, but got %c\n", *peek);
		exit(1);
	}

	char * letter_B = malloc(sizeof(char));
	if(letter_B == NULL){
		fprintf(stderr, "malloc returned NULL. Unexpected!\n");
		exit(1);
	}

	*letter_B = 'B';
	printf("Adding B to queue\n");
	if(queue_add(letter_B, queue)){
		fprintf(stderr, "Adding an element to the queue returned and error\n");
		exit(1);
	}

	printf("Polling queue\n");
	char *poll = queue_poll(queue);
	if(poll == NULL){
		fprintf(stderr, "Expected poll to return a valid pointer but got NULL\n");
		exit(1);
	} else if(poll != letter_A){
		fprintf(stderr, "Expected %p, but got %p\n", letter_A, poll);
		exit(1);
	} else if(*poll != 'A'){
		fprintf(stderr, "Content was modified. Expected A, but got %c\n", *poll);
		exit(1);
	}

	printf("Polling queue\n");
	poll = queue_poll(queue);
	if(poll == NULL){
		fprintf(stderr, "Expected poll to return a valid pointer but got NULL\n");
		exit(1);
	} else if(poll != letter_B){
		fprintf(stderr, "Expected %p, but got %p\n", letter_B, poll);
		exit(1);
	} else if(*poll != 'B'){
		fprintf(stderr, "Content was modified. Expected B, but got %c\n", *poll);
		exit(1);
	}

	printf("Peeking queue (should be empty)\n");
	peek = queue_peek(queue);
	if(peek != NULL){
		fprintf(stderr, "Expected peek to return NULL but got %p\n", peek);
		exit(1);
	}

	printf("Polling queue (should be empty)\n");
	poll = queue_poll(queue);
	if(poll != NULL){
		fprintf(stderr, "Expected poll to return NULL but got %p\n", poll);
		exit(1);
	}

	printf("Freeing queue\n");
	free_queue(queue);
	free(letter_A);
	free(letter_B);

	exit(0);
}
