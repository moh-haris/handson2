
/*
========================================================================================================
Name : Q25
Author : Mohammed Haris
Description :  Write a program to print a message queue's  (use msqid_ds and ipc_perm structures) 
a. access permission 
b. uid, gid 
c. time of last message sent and received    
d. time of last change in the message queue 
d. size of the queue 
f. number of messages in the queue  
g. maximum number of bytes allowed  
h. pid of the msgsnd and msgrcv
Date: 28 Oct, 2025.
========================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <time.h>

int main() {
    key_t key;
    int msgid;
    struct msqid_ds buf;

    
    key = ftok(".", 'm');  
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    msgid = msgget(key, IPC_CREAT | 0666);  
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

   
    if (msgctl(msgid, IPC_STAT, &buf) == -1) {
        perror("msgctl");
        exit(1);
    }

    printf("Message Queue ID: %d\n", msgid);

    printf("Access Permissions: %o\n", buf.msg_perm.mode & 0777);

    printf("UID_owner:- %d\n", buf.msg_perm.uid);
    printf("GID_owner:- %d\n", buf.msg_perm.gid);

    printf("Last message sent: %s", ctime(&buf.msg_stime));

    printf("Last message received: %s", ctime(&buf.msg_rtime));

    printf("Last change: %s", ctime(&buf.msg_ctime));

    printf("Number of messages in queue: %ld\n", buf.msg_qnum);

    printf("Maximum bytes allowed in queue: %ld\n", buf.msg_qbytes);

    printf("PID of last msgsnd: %d\n", buf.msg_lspid);
    printf("PID of last msgrcv: %d\n", buf.msg_lrpid);

    return 0;
}

/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q25$ gcc Q25.c -o Q25
haris@Haris:~/handson2/Q25$ ./Q25
Message Queue ID: 1
Access Permissions: 666
UID (owner): 1000
GID (owner): 1000
Last message sent: Thu Jan  1 00:00:00 1970
Last message received: Thu Jan  1 00:00:00 1970
Last change: Wed Oct  1 05:33:45 2025
Number of messages in queue: 0
Maximum bytes allowed in queue: 16384
PID of last msgsnd: 0
PID of last msgrcv: 0
============================================================================
*/




