
/*
============================================================================
Name : Q12
Author : Mohammed Haris
Description : Write a program to create an orphan process. Use kill system call to send SIGKILL signal to 
the parent process from the child process.
Date: 24th Sept, 2025.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {  
        printf("Child started with PID: %d, parent PID: %d\n", getpid(), getppid());
        sleep(3);

       
        printf("Child sending SIGKILL to parent (PID: %d)\n", getppid());
        kill(getppid(), SIGKILL);

        printf("Parent should be dead now. Child is orphan, adopted\n");
        sleep(8);
        printf("Child exiting \n");
    } 
    else {  
        printf("Parent running with PID: %d, child PID: %d\n", getpid(), pid);
        sleep(10); 
        printf("Parent exiting \n");
    }

    return 0;
}

/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q12$ gcc Q12.c -o Q12
haris@Haris:~/handson2/Q12$ ./Q12
Parent running with PID: 1265, child PID: 1266
Child started with PID: 1266, parent PID: 1265
Child sending SIGKILL to parent (PID: 1265)
Parent should be dead now. Child is orphan, adopted
Killed
============================================================================
*/






