#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/**
 * Experiment No. A6: Critical section using mutex lock
 *
 * Aim:
 * Write a C program to demonstrate Critical section in process synchronization.
 */

int shared_counter = 0;
pthread_mutex_t mutex;

void *increment_counter(void *arg) {
    int thread_id = *(int *)arg;

    printf("Thread %d: Waiting to enter critical section..\n", thread_id);
    pthread_mutex_lock(&mutex);

    /* --- CRITICAL SECTION START --- */
    printf("Thread %d: Entered critical section.\n", thread_id);
    shared_counter++;
    printf("Thread %d: Incremented counter to %d\n", thread_id, shared_counter);
    sleep(1);
    printf("Thread %d: Exiting critical section.\n", thread_id);
    /* --- CRITICAL SECTION END --- */

    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main()
{
    pthread_t threads[3];
    int thread_ids[3] = {1, 2, 3};

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, increment_counter, &thread_ids[i]);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    printf("Final value of shared counter: %d\n", shared_counter);
    return 0;
}
