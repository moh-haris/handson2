/*
============================================================================
Name : 1b
Author : Mohammed Haris
Description :   Write a separate program (for each time domain) to set a interval timer in 10sec and 
10micro second 
       b. . ITIMER_VIRTUAL
Date: 18th Sept, 2025.
============================================================================
*/

#include<stdio.h>
#include <sys/time.h>
#include<signal.h>
#include <unistd.h>

void virtual_alarm_handler(int sig) {
    printf("ITIMER_VIRTUAL alarm\n");
}


int main(){
    struct itimerval time;
    
    signal(SIGVTALRM, virtual_alarm_handler);
    
    time.it_value.tv_sec = 10;
    time.it_value.tv_usec = 10;
    
    time.it_interval.tv_sec = 10;
    time.it_interval.tv_usec = 10;
    
    setitimer(ITIMER_VIRTUAL, &time, NULL);
    while(1){
           for(int i = 0; i<1000; i++);
    }
    return 0;
}


/*
============================================================================
OUTPUT 

haris@Haris:~/handson2/Q1$ gcc 1b.c -o 1b
haris@Haris:~/handson2/Q1$ ./1b
ITIMER_VIRTUAL alarm
ITIMER_VIRTUAL alarm
============================================================================
*/