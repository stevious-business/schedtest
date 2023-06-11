#include "../lib/queue.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

static char expected_output[] = "zmylxkwjviuhtgsfreqdpcobna";

static void verify_alloc(void * ptr){
	if(ptr == NULL){
		fprintf(stderr, "(m/c)alloc returned NULL. Unexpected!\n");
		exit(1);
	}
}

int main(){
	unsigned int letter_count = 'Z' - 'A' + 1;
	printf("There are %u letters in the alphabet. Let's shuffle them (using the alphabet in reversed order)\n", letter_count);

	// calloc will give us \0 at end automatically
	char * alphabet = calloc(letter_count + 1, sizeof(char));
	verify_alloc(alphabet);

	for(unsigned int i = 0; i < letter_count; i++){
		alphabet[i] = 'z' - i;
	}

	printf("Creating three queues\n");
	queue_object *queue_one = new_queue();
	queue_object *queue_two = new_queue();
	queue_object *queue_three = new_queue();
	if(!queue_one || !queue_two || !queue_three) {
		fprintf(stderr, "Expected non NULL value for freshly create queues\n");
		exit(1);
	}

	printf("Moving first half of alphabet into queue_one\n");
	for(unsigned int i = 0; i < letter_count/2; i++){
		if(queue_add(&alphabet[i], queue_one)){
			fprintf(stderr, "Adding an element to the queue returned and error\n");
			exit(1);
		}
	}

	printf("Moving second half of alphabet into queue_two\n");
	for(unsigned int i = letter_count/2; i < letter_count; i++){
		if(queue_add(&alphabet[i], queue_two)){
			fprintf(stderr, "Adding an element to the queue returned and error\n");
			exit(1);
		}
	}

	printf("Merging from queue_one and queue_two into queue_three\n");
	// Queues should have the same length at this point
	while(queue_peek(queue_one) && queue_peek(queue_two)){
		char * value = queue_poll(queue_one);
		queue_add(value, queue_three);

		value = queue_poll(queue_two);
		queue_add(value, queue_three);
	}

	char * val = queue_peek(queue_one);
	if(val != NULL){
		fprintf(stderr, "queue_one was not empty: %c but should be\n", *val);
		exit(1);
	}

	val = queue_peek(queue_two);
	if(val != NULL){
		fprintf(stderr, "queue_two was not empty: %c but should be\n", *val);
		exit(1);
	}

	char *mixed = calloc(letter_count + 1, sizeof(char));
	verify_alloc(mixed);

	printf("Polling from queue_three and creating new string\n");
	for(unsigned int i = 0; i < letter_count; i++){
		char * value = queue_poll(queue_three);
		mixed[i] = *value;
	}

	// original list not needed anymore
	free(alphabet);

	printf("Freeing all three queues\n");
	free_queue(queue_one);
	free_queue(queue_two);
	free_queue(queue_three);

	printf("Result: %s\n", mixed);

	printf("Comparing new string to expected output\n");
	if(strcmp(mixed, expected_output)){
		fprintf(stderr, "New string did not match expected output.\n");
		fprintf(stderr, "Got      | %s\nExpected | %s\n", mixed, expected_output);
		exit(1);
	}

	free(mixed);

	exit(0);
}
