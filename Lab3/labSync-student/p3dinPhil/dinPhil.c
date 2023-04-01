#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

pthread_mutex_t mtx;
pthread_cond_t cond[N];

enum state { THINKING, HUNGRY, EATING };
enum state phil_state[N];

void pickup_forks(int phil);
void putdown_forks(int phil);
void test(int phil);
void *philosopher(void*);

int main() {
    int i, a[N];
    pthread_t tid[N];

    pthread_mutex_init(&mtx, NULL);

    for (i = 0; i < N; i++)
        pthread_cond_init(&cond[i], NULL);

    for (i = 0; i < N; i++) {
        a[i] = i;
        phil_state[i] = THINKING;
        pthread_create(&tid[i], NULL, philosopher, (void*) &a[i]);
    }

    for (i = 0; i < N; i++)
        pthread_join(tid[i], NULL);

    return 0;
}

void *philosopher(void *num) {
    int phil = *(int*) num;

    printf("Philosopher %d has entered room\n", phil);

    while (1) {
        sleep(1);
        pickup_forks(phil);
        eat(phil);
        sleep(2);
        putdown_forks(phil);
        think(phil);
    }
}

void pickup_forks(int phil) {
    pthread_mutex_lock(&mtx);
    phil_state[phil] = HUNGRY;
    printf("Philosopher %d is hungry\n", phil);
    test(phil);
    if (phil_state[phil] != EATING) {
        pthread_cond_wait(&cond[phil], &mtx);
    }
    pthread_mutex_unlock(&mtx);
}

void putdown_forks(int phil) {
    pthread_mutex_lock(&mtx);
    phil_state[phil] = THINKING;
    printf("Philosopher %d is thinking\n", phil);
    test((phil + N - 1) % N);
    test((phil + 1) % N);
    pthread_mutex_unlock(&mtx);
}

void test(int phil) {
    if (phil_state[phil] == HUNGRY &&
        phil_state[(phil + N - 1) % N] != EATING &&
        phil_state[(phil + 1) % N] != EATING) {
        phil_state[phil] = EATING;
        printf("Philosopher %d is eating with forks %d and %d\n",
               phil, (phil + N - 1) % N, phil);
        pthread_cond_signal(&cond[phil]);
    }
}

void eat(int phil)
{
   printf("Philosopher %d is eating\n", phil);
}

void think(int phil)
{
   printf("Philosopher %d is thinking\n", phil);
}