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
    printf("Enter your text:");
    fgets(data,1024,stdin);
    shmdt(data);                        
    printf("Shared memory detached.\n");

    return 0;
}
