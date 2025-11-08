#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>   
#include <unistd.h>

#define NUM_THREADS 3

int shared_memory = 0;
sem_t *semaphore;

void* write_to_shared_memory(void* arg) {
    long tid = (long)arg;

    printf("Thread %ld is waiting to write to shared memory.\n", tid);

    sem_wait(semaphore); 

    int temp = shared_memory;
    printf("Thread %ld reads shared memory: %d\n", tid, temp);

    sleep(1); 

    temp += 10;
    shared_memory = temp;
    printf("Thread %ld writes shared memory: %d\n", tid, shared_memory);

    sem_post(semaphore); 

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
