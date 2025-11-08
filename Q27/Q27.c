#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>


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

    printf("Trying to receive message with flag = 0\n");

    if (msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0) == -1) {
        perror("msgrcv (flag=0)");
    } else {
        printf("Received (flag=0): %s\n", message.msg_text);
    }

    printf("Trying to receive message with IPC_NOWAIT\n");

    if (msgrcv(msgid, &message, sizeof(message.msg_text), 1, IPC_NOWAIT) == -1) {
        if (errno == ENOMSG)
            printf("No message available (IPC_NOWAIT).\n");
        else
            perror("msgrcv (IPC_NOWAIT)");
    } else {
        printf("Received (IPC_NOWAIT): %s\n", message.msg_text);
    }

    return 0;
}

