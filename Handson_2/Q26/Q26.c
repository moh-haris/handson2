
/*
========================================================================================================
Name : Q26
Author : Mohammed Haris
Description : Write a program to send messages to the message queue. Check $ipcs -q
Date: 28 Oct, 2025.
========================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>


struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;
    key = ftok(".", 'm');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    message.msg_type = 1; 
    strcpy(message.msg_text, "Hello, this is a test message");

    if (msgsnd(msgid, &message, sizeof(message.msg_text), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }

    printf("Message sent successfully.\n");

    return 0;
}

/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q26$ gcc Q26.c -o Q26
haris@Haris:~/handson2/Q26$ ./Q26
Message sent successfully.
haris@Haris:~/handson2/Q26$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages
0x41308cbc 0          haris      666        0            0
0x6d308d4c 1          haris      666        0            0
0x6d308e10 2          haris      666        200          2
============================================================================
*/





