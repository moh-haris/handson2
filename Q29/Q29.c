#include <stdio.h>
#include <sys/msg.h>

int main() {
    int msqid = 4;  // replace with actual msqid from ipcs -q
    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
    } else {
        printf("Message queue %d removed successfully.\n", msqid);
    }
    return 0;
}

