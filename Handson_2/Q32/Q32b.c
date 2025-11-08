
/*
========================================================================================================
Name : Q32b
Author : Mohammed Haris
Description :  Write a program to implement semaphore to protect any critical section. 
b. protect shared memory from concurrent write access 
Date: 30 Sept, 2025.
========================================================================================================
*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>   
#include <unistd.h>

#define NUM_THREADS 3

int shared_memory = 0;
sem_t *semaphore;

void* write_to_shared_memory(void* arg) {
    long tid = (long)arg; //extracts the thread ID (which you passed while creating the thread) from the void* argument.

    printf("Thread %ld is waiting to write to shared memory.\n", tid);

    sem_wait(semaphore); 

    int temp = shared_memory;
    printf("Thread %ld reads shared memory: %d\n", tid, temp);

    sleep(1); 

    temp += 10;
    shared_memory = temp;
    printf("Thread %ld writes shared memory: %d\n", tid, shared_memory);

    sem_post(semaphore); //Increases semaphore from 0 → 1
    // Next waiting thread wakes up.

    return NULL;
}

int main() {
    semaphore = sem_open("/shmsem", O_CREAT, 0666, 1);
    if (semaphore == SEM_FAILED) {
        perror("sem_open");
        return 1;
    }

    pthread_t threads[NUM_THREADS];

    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, write_to_shared_memory, (void*)i);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_close(semaphore);
    sem_unlink("/shmsem"); 

    return 0;
}

/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q32$ gcc Q32b.c -o Q32b
haris@Haris:~/handson2/Q32$ ./Q32b
Thread 0 is waiting to write to shared memory.
Thread 0 reads shared memory: 0
Thread 1 is waiting to write to shared memory.
Thread 2 is waiting to write to shared memory.
Thread 0 writes shared memory: 10
Thread 1 reads shared memory: 10
Thread 1 writes shared memory: 20
Thread 2 reads shared memory: 20
Thread 2 writes shared memory: 30
============================================================================
*/







