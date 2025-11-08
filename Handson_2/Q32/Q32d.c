
/*
========================================================================================================
Name : Q32d
Author : Mohammed Haris
Description :  Write a program to implement semaphore to protect any critical section. 
d. remove the created semaphore    
Date: 30 Sept, 2025.
========================================================================================================
*/
/*Here we used unnamed semaphore(sem_init()) to demonstrate semaphore destruction. what is unnamed semphore here is the answer . Unnamed Semaphore (sem_init)

Used when:
-> Only threads created by the same process can use it and No need to unlink anything
✅ Threads are inside the same process. Where as sem_open named semaphore used when Intended for multiple programs sharing a semaphore, Any different program (different process) can open the same semaphore by name */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 3
#define NUM_RESOURCES 2

sem_t sem; // Declare semaphore sem_t sem;



A counting semaphore stored in a variable.

void* use_resource(void* arg) {
    long tid = (long)arg;

    printf("Thread %ld is waiting for a resource.\n", tid);
    sem_wait(&sem);  

    printf("Thread %ld has acquired a resource.\n", tid);
    sleep(2);       

    printf("Thread %ld is releasing the resource.\n", tid);
    sem_post(&sem);  

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    sem_init(&sem, 0, NUM_RESOURCES); 

    for (long i = 0; i < NUM_THREADS; i++)
        pthread_create(&threads[i], NULL, use_resource, (void*)i);

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    sem_destroy(&sem);
    printf("Semaphore destroyed successfully.\n");

    return 0;
}


/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q32$ ./Q32
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







