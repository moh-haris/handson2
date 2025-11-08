#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
    int choice, init_val;
    key_t key;
    int semid;

    printf("Semaphore Creation Program\n");
    printf("1. Binary Semaphore\n");
    printf("2. Counting Semaphore\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    key = ftok(".", 's');
    if (key == -1) { perror("ftok"); exit(1); }

    semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1) { perror("semget"); exit(1); }

    if (choice == 1) {
        if (semctl(semid, 0, SETVAL, 1) == -1) {
            perror("semctl");
            exit(1);
        }
        printf("Binary semaphore created with ID = %d, initialized to 1.\n", semid);
    }
    else if (choice == 2) {
        printf("Enter initial value for counting semaphore: ");
        scanf("%d", &init_val);

        if (semctl(semid, 0, SETVAL, init_val) == -1) {
            perror("semctl");
            exit(1);
        }
        printf("Counting semaphore created with ID = %d, initialized to %d.\n", semid, init_val);
    }
    else {
        printf("Invalid choice.\n");
    }

    return 0;
}
