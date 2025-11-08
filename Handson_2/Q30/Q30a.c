
/*
========================================================================================================
Name : Q30a
Author : Mohammed Haris
Description : Write a program to create a shared memory. 
a. write some data to the shared memory 
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
    printf("Enter your data:");
    fgets(data, 1024, stdin);
    shmdt(data);                        
    printf("Shared memory detached.\n");

    return 0;
}

/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q30$ gcc Q30.c -o Q30a
haris@Haris:~/handson2/Q30$ ./Q30a
Shared memory attached.
Enter your text:Hello Haris
Shared memory detached.
============================================================================
*/






