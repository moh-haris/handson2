

/*
============================================================================
Name : Q15
Author : Mohammed Haris
Description : Write a simple program to send some data from parent to the child process. 
Date: 24th Sept, 2025.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int pipefds[2];
    if (pipe(pipefds) == -1) {
        perror("pipe failed");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }
    
    else if (pid == 0) {
        close(pipefds[0]);

        int number = 42;
        printf("Child: sending %d to parent...\n", number);

        if (write(pipefds[1], &number, sizeof(number)) == -1) {
            perror("write failed");
            exit(1);
        }

        close(pipefds[1]);
    }
    else {
        close(pipefds[1]);

        int received = 0;
        if (read(pipefds[0], &received, sizeof(received)) == -1) {
            perror("read failed");
            exit(1);
        }

        printf("Parent: received %d from child\n", received);

        close(pipefds[0]);
    }

    return 1;
}

/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q15$ gcc Q15.c -o Q15
haris@Haris:~/handson2/Q15$ ./Q15
Child: sending 42 to parent...
Parent: received 42 from child
============================================================================
*/
