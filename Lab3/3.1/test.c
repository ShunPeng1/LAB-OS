#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAXCOUNT 1000000000

static int count = 0;
static pthread_mutex_t lock ;

void *count_func(void *sid) {
    int i;
    for (i = 0; i < MAXCOUNT; i++) {
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
    pthread_create(&thread1, NULL, count_func, "1");
    pthread_create(&thread2, NULL, count_func, "2");

    /* Wait for thread 1 to finish */
    pthread_join(thread1, NULL);

    /* Wait for thread 2 to finish */
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&lock);
    return 0;
}
