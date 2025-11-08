/*
============================================================================
Name : 1a.c
Author : Mohammed Haris
Description :   Write a separate program (for each time domain) to set a interval timer in 10sec and 
10micro second 
       a. ITIMER_REAL 
Date: 18th Sept, 2025.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

void handler(int sig) {
    printf("ITIMER_REAL fired!\n");
}

int main() {
    struct itimerval t = { {10, 10}, {10, 10} }; 

    signal(SIGALRM, handler);
    setitimer(ITIMER_REAL, &t, NULL);

    while (1) pause();  
}


/*
============================================================================
OUTPUT 

haris@Haris:~/handson2/Q1$ gcc 1c.c -o 1c
haris@Haris:~/handson2/Q1$ ./1c
ITIMER_REAL fired!
ITIMER_REAL fired!
============================================================================
*/
