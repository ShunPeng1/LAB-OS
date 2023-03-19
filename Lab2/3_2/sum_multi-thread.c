#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* sum(void* arg) {
    int* range = (int*) arg;
    int start = range[0];
    int end = range[1];
    int* result = malloc(sizeof(int));
    *result = 0;
    for (int i = start; i <= end; i++) {
        *result += i;
    }
    pthread_exit(result);
}

int main(int argc, char* argv[]) {
    int n = atoi(argv[2]);
    int num_threads = atoi(argv[1]);
    int range_size = n / num_threads;
    pthread_t threads[num_threads];
    int results[num_threads];
    int start = 1;
    int end = range_size;
    for (int i = 0; i < num_threads; i++) {
        int* range = malloc(2 * sizeof(int));
        range[0] = start;
        range[1] = end;
        start = end + 1;
        end = start + range_size - 1;
        if (i == num_threads - 1) {
            end = n;
        }
        pthread_create(&threads[i], NULL, sum, (void*) range);
    }
    int sum = 0;
    for (int i = 0; i < num_threads; i++) {
        int* result;
        pthread_join(threads[i], (void**) &result);
        sum += *result;
        free(result);
    }
    printf("Sum of 1 to %d is %d\n", n, sum);
    return 0;
}
