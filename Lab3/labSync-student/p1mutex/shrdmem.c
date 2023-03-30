#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int MAX_COUNT = 1e9;
static int count = 0;
static pthread_mutex_t lock ;

void *f_count(void *sid) {
    int i;
    for (i = 0; i < MAX_COUNT; i++) {
        pthread_mutex_lock(&lock);
        count++;
        pthread_mutex_unlock(&lock);
    }
    pthread_mutex_lock(&lock);
    printf("Thread %s: holding %d\n", (char *) sid, count);
    pthread_mutex_unlock(&lock);
    return NULL;
}



int main() {
    pthread_mutex_init(&lock, NULL);

    pthread_t thread1, thread2;
    /* Create independent threads each of which will execute function */
    pthread_create(&thread1, NULL, f_count, "1");
    pthread_create(&thread2, NULL, f_count, "2");

    /* Wait for thread 1 to finish */
    pthread_join(thread1, NULL);

    /* Wait for thread 2 to finish */
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&lock);
    return 0;
}

