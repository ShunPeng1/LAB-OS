
#ifndef QUEUE_H
#define QUEUE_H

#include "structs.h"

/* Initialize the process queue */
void initialize_queue(struct pqueue_t * q);

/* Get a process from a queue */
struct pcb_t * de_queue(struct pqueue_t * q);

/* Put a process into a queue */
void en_queue(struct pqueue_t * q, struct pcb_t * proc);

/* Return and delete a process with first highest prioirty in a queue */
struct pcb_t* pick_out_first_highest_priority(struct pqueue_t * q);

int empty(struct pqueue_t * q);

#endif


