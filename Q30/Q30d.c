#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

int main() {
    key_t key = ftok(".", 'a');          
    int shmid = shmget(key, 1024, 0);    

    if (shmid == -1) {
        printf("No shared memory exists with this key.\n");
        return 1;
    }

    if (shmctl(shmid, IPC_RMID, NULL) == -1) {  
        printf("Failed to remove shared memory.\n");
        return 1;
    }

    printf("Shared memory removed successfully.\n");
    return 0;
}
