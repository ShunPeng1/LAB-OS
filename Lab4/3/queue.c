
#include <stdlib.h>
#include "queue.h"
#include <pthread.h>
#include <stdio.h>


/* Remember to initilize the queue before using it */
void initialize_queue(struct pqueue_t * q) {
	q->head = q->tail = NULL;
	pthread_mutex_init(&q->lock, NULL);
}

/* Return non-zero if the queue is empty */
int empty(struct pqueue_t * q) {
	return (q->head == NULL);
}

/* Get PCB of a process from the queue (q).
 * Return NULL if the queue is empty */
struct pcb_t * de_queue(struct pqueue_t * q) {
	struct pcb_t * proc = NULL;
	// TODO: return q->head->data and remember to update the queue's head
	// and tail if necessary. Remember to use 'lock' to avoid race
	// condition
	

	pthread_mutex_lock(&q->lock);
	// YOUR CODE HERE
	
	//printf("dequeue begin\n");
	if(q->head == NULL){

	}
	else if(q->head == q->tail){
		proc = q->head->data;
		
		free(q->head);
		q->head = q->tail = NULL;
	}
	else{
		proc = q->head->data;
		struct qitem_t * temp = q->head->next; 
		free(q->head);
		q->head = temp;
	}


	//printf("dequeue end\n");
	pthread_mutex_unlock(&q->lock);

	return proc;
}

/* Put PCB of a process to the queue. */
void en_queue(struct pqueue_t * q, struct pcb_t * proc) {
	// TODO: Update q->tail.
	// Remember to use 'lock' to avoid race condition
	
	// YOUR CODE HERE

	pthread_mutex_lock(&q->lock);
	//printf("enqueue begin\n");

	struct qitem_t* item = malloc(sizeof(struct qitem_t));
	item->next = NULL;
	item->data = proc;

	if(q->tail == NULL){
		q->tail = q->head = item;
	}
	else{
		q->tail->next = item;
		q->tail = item;
	}

	//("enqueue end\n");
	pthread_mutex_unlock(&q->lock);
}


/* Return and delete a process with first highest prioirty in a queue */
struct pcb_t* pick_out_first_highest_priority(struct pqueue_t * q){
	if(q->head == NULL){
		return NULL;
	}

	pthread_mutex_lock( &q->lock);
	
	//printf("Find %d->",  q->head->data->arrival_time);
	// Find first highest priority
	int highestPriority = q->head->data->priority;
	struct qitem_t* highestPriorityItem = q->head, *currentItem = q->head, *lastHighestPriorityItem = NULL;
	while(currentItem->next != NULL){
		struct qitem_t * next = currentItem->next;

		if(next->data->priority > highestPriority){
			highestPriority = next->data->priority;
			lastHighestPriorityItem = currentItem;
			highestPriorityItem = next;
		}
		//printf("%d->",currentItem->next->data->arrival_time);
		currentItem = next;
	}

	struct pcb_t *proc = NULL;
	
	//printf("\nRemove arrival time: %d, burst time: %d, priority: %d\n", highestPriorityItem->data->arrival_time, highestPriorityItem->data->burst_time, highestPriorityItem->data->priority);
	
	// Remove first highest priority 
	if(q->head == q->tail){
		proc = q->head->data;
		
		free(q->head);
		q->head = q->tail = NULL;
	}
	else if(q->head == highestPriorityItem){
		proc = q->head->data;

		struct qitem_t * temp = q->head->next; 
		free(q->head);
		q->head = temp;
	}
	else if(q->tail == highestPriorityItem){
		proc = q->tail->data;

		//printf("Last %d\n", lastHighestPriorityItem->data->arrival_time);
		free(q->tail);
		q->tail = lastHighestPriorityItem;
		q->tail->next = NULL;
	}
	else{
		proc = highestPriorityItem->data;

		//printf("Last %d\n", lastHighestPriorityItem->data->arrival_time);
		lastHighestPriorityItem->next = highestPriorityItem->next;
		free(highestPriorityItem);
	}


	pthread_mutex_unlock(&q->lock);

	return proc;
}


