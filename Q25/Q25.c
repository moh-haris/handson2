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
