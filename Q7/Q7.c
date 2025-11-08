
/*
============================================================================
Name : Q7
Author : Mohammed Haris
Description : Write a simple program to print the created thread ids.
Date: 23th Sept, 2025.
============================================================================
*/

#include <stdio.h>
#include <pthread.h>


void* worker(void* arg) {
    int tid = *(int*)arg;
    printf("Thread %lu is running with logical id %d\n", pthread_self(), tid);
    return NULL;
}

int main() {
    pthread_t threads[3];
    int ids[] = {1, 2, 3};

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

haris@Haris:~/handson2/Q7$ gcc Q7.c -o Q7
haris@Haris:~/handson2/Q7$ ./Q7
Thread 135619284039360 is running with logical id 1
Thread 135619275646656 is running with logical id 2
Thread 135619267253952 is running with logical id 3
============================================================================
*/

