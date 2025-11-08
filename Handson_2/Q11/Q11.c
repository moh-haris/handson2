
/*
============================================================================
Name : Q11
Author : Mohammed Haris
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal -  
use sigaction system call.
Date: 24th Sept, 2025.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
    struct sigaction ignore_act, default_act;


    ignore_act.sa_handler = SIG_IGN;
    sigemptyset(&ignore_act.sa_mask);
    ignore_act.sa_flags = 0;

   
    default_act.sa_handler = SIG_DFL;
    sigemptyset(&default_act.sa_mask);
    default_act.sa_flags = 0;

  
    if (sigaction(SIGINT, &ignore_act, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }
    printf("SIGINT is ignored for 5 seconds. Press Ctrl+C \n");
    sleep(5);

   
    if (sigaction(SIGINT, &default_act, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }
    printf("SIGINT restored to default. Press Ctrl+C to terminate the program.\n");

   
    while (1) {
        pause(); 
    }

    return 0;
}

/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q11$ gcc Q11.c -o Q11
haris@Haris:~/handson2/Q11$ ./Q11
SIGINT is ignored for 5 seconds. Press Ctrl+C
^C
SIGINT restored to default. Press Ctrl+C to terminate the program.
^C
============================================================================
*/




