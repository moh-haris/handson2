
/*
========================================================================================================
Name : Q29
Author : Mohammed Haris
Description : Write a program to remove the message queue.
b. with IPC_NOWAIT as a flag
Date: 29 Sept, 2025.
========================================================================================================
*/

#include <stdio.h>
#include <sys/msg.h>

int main() {
    int msqid = 4; 
    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
    } else {
        printf("Message queue %d removed successfully.\n", msqid);
    }
    return 0;
}

/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q29$ gcc Q29.c -o Q29
haris@Haris:~/handson2/Q29$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages
0x41308cbc 0          haris      666        0            0
0x6d308d4c 1          haris      666        0            0
0x6d308e10 2          haris      666        200          2
0x6d308e13 3          haris      666        0            0
0x61308e15 4          haris      777        0            0
haris@Haris:~/handson2/Q29$ ./Q29
Message queue 4 removed successfully.
haris@Haris:~/handson2/Q29$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages
0x41308cbc 0          haris      666        0            0
0x6d308d4c 1          haris      666        0            0
0x6d308e10 2          haris      666        200          2
0x6d308e13 3          haris      666        0            0
============================================================================
*/






