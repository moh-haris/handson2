
/*
============================================================================
Name : Q13b
Author : Mohammed Haris
Description :  Write two programs: The second program 
will send the signal (using kill system call). Find out whether the first program is able to catch 
the signal or not. 
Date: 24th Sept, 2025.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main() {
    pid_t pid;

    printf("Enter PID of target process: ");
    if (scanf("%d", &pid) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (kill(pid, SIGSTOP) == 0) {
        printf("Successfully sent SIGSTOP to process %d\n", pid);
    } else {
        perror("Error sending SIGSTOP");
    }

    return 0;
}

/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q13$ gcc Q13.c -o Q13
haris@Haris:~/handson2/Q13$ ./Q13b
Enter PID of target process: 1373
Successfully sent SIGSTOP to process 1373
============================================================================
*/








