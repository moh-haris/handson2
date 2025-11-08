

/*
============================================================================
Name : Q13a
Author : Mohammed Haris
Description :  Write two programs: first program is waiting to catch SIGSTOP signal
Date: 24th Sept, 2025.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("Caught signal %d\n", sig);
    exit(0);
}

int main() {
    printf("Receiver program started with PID: %d\n", getpid());

    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

   
    if (sigaction(SIGSTOP, &sa, NULL) == -1) {
        perror("sigaction failed");
    }

    printf("Waiting for SIGSTOP\n");

   
    while (1) {
        pause();
    }

    return 0;
}


/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q13$ gcc Q13.c -o Q13
haris@Haris:~/handson2/Q13$ ./Q13
Receiver program started with PID: 1373
sigaction failed: Invalid argument
Waiting for SIGSTOP

[1]+  Stopped
============================================================================
*/







