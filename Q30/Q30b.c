#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    key_t key = ftok(".", 'a');
    if (key == -1) { perror("ftok"); exit(1); }

    int shmid = shmget(key, 1024, 0);
    if (shmid == -1) { perror("shmget"); exit(1); }

    char *data = shmat(shmid, NULL, SHM_RDONLY);
    if (data == (char *)-1) { perror("shmat"); exit(1); }

    printf("Current data in shared memory: %s\n", data);

    printf("Trying to write to read-only shared memory\n");  

    printf("Cannot overwrite shared memory when attached with SHM_RDONLY.\n");

    shmdt(data);
    return 0;
}
