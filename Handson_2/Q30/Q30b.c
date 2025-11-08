/*
========================================================================================================
Name : Q30b
Author : Mohammed Haris
Description : Write a program to create a shared memory. 
b. attach with O_RDONLY and check whether you are able to overwrite. 
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
    if (key == -1) { perror("ftok"); exit(1); }

    int shmid = shmget(key, 1024, 0);
    if (shmid == -1) { perror("shmget"); exit(1); }

    char *data = shmat(shmid, NULL, SHM_RDONLY);
    if (data == (char *)-1) { perror("shmat"); exit(1); }

    printf("Current data in shared memory: %s\n", data);

    printf("Trying to write to read-only shared memory\n");

    printf("Cannot overwrite shared memory when attached with SHM_RDONLY.\n");

    shmdt(data);
    return 0;
}

/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q30$ gcc Q30b.c -o Q30b
haris@Haris:~/handson2/Q30$ ./Q30b
Current data in shared memory: Hello Haris

Trying to write to read-only shared memory
Cannot overwrite shared memory when attached with SHM_RDONLY.
============================================================================
*/






