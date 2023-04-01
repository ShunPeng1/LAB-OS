#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "seqlock.h"  /* TODO implement this header file */

pthread_seqlock_t lock;

#define MAX_VALUE 1000000


int shared_value = 0;

void* reader(void* arg) {
    int id = *((int*) arg);
    unsigned seq_before, seq_after;
    int local_value;

    for(int i = 0; i < 100; i++) {
        seq_before = pthread_seqlock_rdlock(&lock);
        local_value = shared_value;
        seq_after = pthread_seqlock_rdunlock(&lock);

        printf("Reader %d read shared value %d with seq_before = %u and seq_after = %u\n", id, local_value, seq_before, seq_after);
        if(seq_before!=seq_after) {
         printf("\nDIFFER\n");
         //printf("Reader %d read shared value %d with seq_before = %u and seq_after = %u\n", id, local_value, seq_before, seq_after);
        
        }
        usleep(rand() % 1000);
    }

    pthread_exit(NULL);
}

void* writer(void* arg) {
    int id = *((int*) arg);
    unsigned seq_before, seq_after;

    for(int i = 0; i < 100; i++) {
        pthread_seqlock_wrlock(&lock);
        shared_value++;
        pthread_seqlock_wrunlock(&lock);

        printf("Writer %d wrote shared value %d\n", id, shared_value);
        usleep(rand() % 1000);
    }

    pthread_exit(NULL);
}

int test() {
    pthread_t readers[50], writers[20];
    int reader_ids[50], writer_ids[20];

    pthread_seqlock_init(&lock);

    for(int i = 0; i < 50; i++) {
        reader_ids[i] = i;
        pthread_create(&readers[i], NULL, reader, (void*) &reader_ids[i]);
    }

    for(int i = 0; i < 20; i++) {
        writer_ids[i] = i;
        pthread_create(&writers[i], NULL, writer, (void*) &writer_ids[i]);
    }

    for(int i = 0; i < 50; i++) {
        pthread_join(readers[i], NULL);
    }

    for(int i = 0; i < 20; i++) {
        pthread_join(writers[i], NULL);
    }

    return 0;
}


int main()
{
   //test();
   
   int val = 0;
   pthread_seqlock_init(&lock);

   //printf("init val = %d\n", val); 
   pthread_seqlock_wrlock(&lock);
   val++;
   //printf("writer val = %d\n", val); 
   pthread_seqlock_wrunlock(&lock);

   //printf("before reader val = %d\n", val); 
   if(pthread_seqlock_rdlock(&lock) == 1){
      printf("val = %d\n", val); 
      pthread_seqlock_rdunlock(&lock);
   }
   //printf("end val = %d\n", val); 
   
}
