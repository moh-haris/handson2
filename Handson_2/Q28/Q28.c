/*
========================================================================================================
Name : Q28
Author : Mohammed Haris
Description :  Write a program to change the exiting message queue permission. (use msqid_ds structure)
b. with IPC_NOWAIT as a flag
Date: 29 Sept, 2025.
========================================================================================================
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    key_t key = ftok(".", 'a');
    if (key == -1) { perror("ftok"); exit(1); }

    int msqid = msgget(key, IPC_CREAT | 0666);
    if (msqid == -1) { perror("msgget"); exit(1); }
    struct msqid_ds st;
    if (msgctl(msqid, IPC_STAT, &st) == -1) { perror("msgctl"); exit(1); }
    printf("Current access Permissions: %o\n", st.msg_perm.mode);
    st.msg_perm.mode = 0777;
    if (msgctl(msqid, IPC_SET, &st) == -1) { perror("msgctl"); exit(1); }
    if (msgctl(msqid, IPC_STAT, &st) == -1) { perror("msgctl"); exit(1); }
    printf("New access Permissions: %o\n", st.msg_perm.mode);

    return 0;
}

/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q28$ gcc Q28.c -o Q28
haris@Haris:~/handson2/Q28$ ./Q28
Current access Permissions: 666
New access Permissions: 777

============================================================================
*/






