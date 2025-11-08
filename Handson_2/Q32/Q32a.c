
/*
========================================================================================================
Name : Q32a
Author : Mohammed Haris
Description :  Write a program to implement semaphore to protect any critical section. 
a. rewrite the ticket number creation program using semaphore 
Date: 30 Sept, 2025.
========================================================================================================
*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>   
#include <unistd.h>

#define NUM_THREADS 3

int ticket_number = 0;
sem_t *semaphore;

void* generate_ticket(void* arg) {
    long tid = (long)arg;
    printf("Thread %ld is waiting to generate a ticket.\n", tid);
    sem_wait(semaphore); 
    ticket_number++;
    printf("Thread %ld generated ticket number: %d\n", tid, ticket_number);
    sleep(1); 
    sem_post(semaphore);  //Increases semaphore from 0 → 1
    // Next waiting thread wakes up.

    return NULL;
}
int main() {
   
    semaphore = sem_open("/ticketsem", O_CREAT, 0666, 1); /*✅ Creates a named semaphore called "/ticketsem"
✅ O_CREAT → create if not exists
✅ Permission → 0666 (everyone can read/write)
✅ Initial value = 1 → acts like a binary semaphore
More about named semaphore:- can be shared between unrelated processes using the name. persist unitl you manually delete it using sem_unlink().
This ensures only one thread can enter the critical section.*/
    if (semaphore == SEM_FAILED) {
        perror("sem_open");
        return 1;
    }
    pthread_t threads[NUM_THREADS];
    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, generate_ticket, (void*)i);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL); /*pthread_join(threads[i], NULL);
Main waits for all threads to finish.*/
    }
    sem_close(semaphore);
    sem_unlink("/ticketsem"); 

    return 0;
}

/*Summary here thread 0,1 and 2 enter into the generate_ticket functions only thread 0 allowed to enter at that time other 2 thread waiting at sem_wait() as soon as thread 0 up the sem any 1 out of 2 thread can enter */

/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q32$ gcc Q32a.c -o Q32
haris@Haris:~/handson2/Q32$ ./Q32
Thread 0 is waiting to generate a ticket.
Thread 0 generated ticket number: 1
Thread 1 is waiting to generate a ticket.
Thread 2 is waiting to generate a ticket.
Thread 1 generated ticket number: 2
Thread 2 generated ticket number: 3
============================================================================
*/







