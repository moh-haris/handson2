/*
============================================================================
Name : Q6
Author : Mohammed Haris
Description : Write a simple program to create three threads. 
Date: 21th Sept, 2025.
============================================================================
*/

#include <stdio.h>
#include <pthread.h>

void* worker(void* arg) {
    int tid = *(int*)arg;
    printf("Thread %d is running\n", tid);
    return NULL;
}

int main() {
    pthread_t threads[3];
    int ids[3] = {1, 2, 3};

    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, worker, &ids[i]);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
}

/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q5$ gcc Q5.c -o 5
haris@Haris:~/handson2/Q5$ ./5
Thread 1 is running
Thread 2 is running
Thread 3 is running
============================================================================
*/
