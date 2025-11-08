
/*
========================================================================================================
Name : Q32c
Author : Mohammed Haris
Description :  Write a program to implement semaphore to protect any critical section. 
c. protect multiple pseudo resources ( may be two) using counting semaphore 
Date: 30 Sept, 2025.
========================================================================================================
*/

//Pseudo resource means a fake or simulated resource used only for learning/demonstration — not a real hardware resource.
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>

#define NUM_THREADS 5

sem_t *semaphore; //unnamed semphore

void* critical_section(void* arg) {
    long thread_id = (long)arg;

    printf("Thread %ld is waiting to enter critical section.\n", thread_id);

    sem_wait(semaphore); 
    printf("Thread %ld has entered the critical section.\n", thread_id);

    sleep(2); 

    printf("Thread %ld is leaving the critical section.\n", thread_id);
    sem_post(semaphore); 

    return NULL;
}

int main() {
    semaphore = sem_open("/countsem", O_CREAT, 0666, 2); //counting sem with initial value 2
    if (semaphore == SEM_FAILED) {
        perror("sem_open");
        return 1;
    }

    pthread_t threads[NUM_THREADS];

    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, critical_section, (void*)i);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_close(semaphore);
    sem_unlink("/countsem");  

    return 0;
}


/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q32$ gcc Q32c.c -o Q32
haris@Haris:~/handson2/Q32$ ./Q32
Thread 0 is waiting to enter critical section.
Thread 0 has entered the critical section.
Thread 1 is waiting to enter critical section.
Thread 1 has entered the critical section.
Thread 2 is waiting to enter critical section.
Thread 3 is waiting to enter critical section.
Thread 4 is waiting to enter critical section.
Thread 1 is leaving the critical section.
Thread 0 is leaving the critical section.
Thread 3 has entered the critical section.
Thread 2 has entered the critical section.
Thread 3 is leaving the critical section.
Thread 2 is leaving the critical section.
Thread 4 has entered the critical section.
Thread 4 is leaving the critical section.
============================================================================
*/







