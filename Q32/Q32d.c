#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 3
#define NUM_RESOURCES 2

sem_t sem;

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
