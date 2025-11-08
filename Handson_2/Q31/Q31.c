/*
========================================================================================================
Name : Q31
Author : Mohammed Haris
Description :Write a program to create a semaphore and initialize value to the semaphore. 
a. create a binary semaphore 
b. create a counting semaphore 
Date: 29 Sept, 2025.
========================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
    int choice, init_val;
    key_t key;
    int semid;

    printf("Semaphore Creation Program\n");
    printf("1. Binary Semaphore\n");
    printf("2. Counting Semaphore\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    key = ftok(".", 's'); // ftok is file to key ensures two processes using the same path + same char will get the same key, so they can share the same semaphore.
    if (key == -1) { perror("ftok"); exit(1); }

    semid = semget(key, 1, IPC_CREAT | 0666); // Creates a semaphore set and returns it id or returns semid for existing IPC_CREAT = create if not existssemaphore set. 1 = number of semaphores in this set
    if (semid == -1) { perror("semget"); exit(1); }

    if (choice == 1) {
        if (semctl(semid, 0, SETVAL, 1) == -1) { // SETVAL to 1 for binary semaphore setting value for semaphore 
            perror("semctl");
            exit(1);
        }
        printf("Binary semaphore created with ID = %d, initialized to 1.\n", semid);
    }
    else if (choice == 2) {
        printf("Enter initial value for counting semaphore: ");
        scanf("%d", &init_val);

        if (semctl(semid, 0, SETVAL, init_val) == -1) {
            perror("semctl");
            exit(1);
        }
        printf("Counting semaphore created with ID = %d, initialized to %d.\n", semid, init_val);
    }
    else {
        printf("Invalid choice.\n");
    }

    return 0;
}

/*e semaphore can only be used to synchronize one resource, i.e. one
 critical section, so if your program has like 10 critical sections then you’ll need 10 semaphores.*/

/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q31$ gcc Q31.c -o Q31
haris@Haris:~/handson2/Q31$ ./Q31
Semaphore Creation Program
1. Binary Semaphore
2. Counting Semaphore
Enter choice: 1
Binary semaphore created with ID = 0, initialized to 1.
haris@Haris:~/handson2/Q31$ ./Q31
Semaphore Creation Program
1. Binary Semaphore
2. Counting Semaphore
Enter choice: 2
Enter initial value for counting semaphore: 3
Counting semaphore created with ID = 0, initialized to 3.
============================================================================
*/







