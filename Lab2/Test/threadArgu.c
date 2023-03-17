#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 5


struct thread_data{
    int thread_id;
    int sum;
    char *message;
}

struct thread_data thread_data_array[NUM_THREADS];

void *PrintHello (void *thread_arg)
{
struct thread data xmy data;

my data = (struct thread data x) thread arg;
taskid = my data—>thread id;

sum = my data—sum;

hello msg = my data—>message;

}
int main (int argc, char xargv|[])

{

thread data _array[t].thread id = t;

thread data array[t].sum = sum;

thread data _array[t]. message = messages|t];

rc = pthread create(&threads|[t], NULL, PrintHello,
(void x) &thread data array[t]);
