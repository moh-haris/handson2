/*
========================================================================================================
Name : Q30c
Author : Mohammed Haris
Description : Write a program to create a shared memory. 
c. detach the shared memory 
Date: 29 Sept, 2025.
========================================================================================================
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    key_t key = ftok(".", 'a');         
    int shmid = shmget(key, 1024, IPC_CREAT | 0666); 

    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }
    char *data = shmat(shmid, NULL, 0);  
    if (data == (char *)-1) {
        perror("shmat failed");
        exit(1);
    }
    printf("Shared memory attached.\n");
    shmdt(data);                        
    printf("Shared memory detached.\n");

    return 0;
}

/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q30$ gcc Q30c.c -o Q30c
haris@Haris:~/handson2/Q30$ ./Q30c
Shared memory attached.
Shared memory detached.
============================================================================
*/






