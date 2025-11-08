/*
============================================================================
Name : 1c
Author : Mohammed Haris
Description :   Write a separate program (for each time domain) to set a interval timer in 10sec and 
10micro second 
       c. ITIMER_PROF 
Date: 18th Sept, 2025.
============================================================================
*/

#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

void handle_prof_alarm(int signo) {
    printf("ITIMER_PROF triggered\n");
}

int main() {
    struct itimerval my_timer;

    signal(SIGPROF, handle_prof_alarm);

    my_timer.it_value.tv_sec = 10;
    my_timer.it_value.tv_usec = 10;

    my_timer.it_interval.tv_sec = 10;
    my_timer.it_interval.tv_usec = 10;

    setitimer(ITIMER_PROF, &my_timer, NULL);

    while (1) {
        
        for (int j = 0; j < 1000; j++) {
            
        }
    }
    return 0;
}

/*
============================================================================
OUTPUT 

haris@Haris:~/handson2/Q1$ gcc 1c.c -o 1c
haris@Haris:~/handson2/Q1$ ./1c
ITIMER_PROF triggered
ITIMER_PROF triggered
============================================================================
*/