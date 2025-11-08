/*
========================================================================================================
Name : Q24
Author : Mohammed Haris
Description :   Write a program to create a message queue and print the key and message queue id. 
Date: 27 Oct, 2025.
========================================================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

int main() {
    key_t key;
    int msgid;

    key = ftok("progfile", 65);  
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Key: %d\n", key);
    printf("Message Queue ID: %d\n", msgid);

    return 0;
}

/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q24$ touch progfile
haris@Haris:~/handson2/Q24$ gcc Q24.c -o Q24
haris@Haris:~/handson2/Q24$ ./Q24
Key: 1093700796
Message Queue ID: 0
============================================================================
*/




