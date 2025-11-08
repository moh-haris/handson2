#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>

#define NUM_THREADS 5

sem_t *semaphore;

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
    semaphore = sem_open("/countsem", O_CREAT, 0666, 2);
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
