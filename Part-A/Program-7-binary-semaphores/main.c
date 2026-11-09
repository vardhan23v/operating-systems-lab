#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

/**
 * Part A - Program 7: Semaphores using binary semaphores
 *
 * Exam Question:
 * Write a C program to demonstrate Semaphores using binary semaphores.
 */

sem_t semaphore;

void *thread_function(void *arg) {
    int thread_id = *(int *)arg;

    printf("Thread %d: Waiting to enter critical section..\n", thread_id);
    sem_wait(&semaphore);

    /* --- CRITICAL SECTION START --- */
    printf("Thread %d: Entered critical section.\n", thread_id);
    sleep(1);
    printf("Thread %d: Leaving critical section.\n", thread_id);
    /* --- CRITICAL SECTION END --- */

    sem_post(&semaphore);
    return NULL;
}

int main()
{
    pthread_t threads[3];
    int thread_ids[3] = {1, 2, 3};

    /* Binary semaphore: pshared = 0 (threads of same process), initial value = 1 */
    sem_init(&semaphore, 0, 1);

    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&semaphore);
    printf("All threads have finished execution.\n");
    return 0;
}
