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
    sem_post(semaphore); 

    return NULL;
}
int main() {
   
    semaphore = sem_open("/ticketsem", O_CREAT, 0666, 1);
    if (semaphore == SEM_FAILED) {
        perror("sem_open");
        return 1;
    }
    pthread_t threads[NUM_THREADS];
    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, generate_ticket, (void*)i);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    sem_close(semaphore);
    sem_unlink("/ticketsem"); 

    return 0;
}
