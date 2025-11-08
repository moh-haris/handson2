/*
============================================================================
Name : Q9
Author : Mohammed Haris
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT 
signal -  Use signal system call.
Date: 24th Sept, 2025.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void dummy_handler(int sig) {
    printf("Currently ignoring SIGINT\n");
}

int main() {
    
    signal(SIGINT, dummy_handler);
    printf("Custom handler installed. Try pressing Ctrl+C (ignored for 5 seconds).\n");
    sleep(5);

    
    signal(SIGINT, SIG_IGN);
    printf("Now SIGINT is being ignored completely for 5 seconds.\n");
    sleep(5);

   
    signal(SIGINT, SIG_DFL);
    printf("SIGINT restored to default. Press Ctrl+C to exit.\n");

   
    while (1) {
        pause(); 
    }

    return 0;
}

/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q9$ gcc Q9.c -o Q9
haris@Haris:~/handson2/Q9$ ./Q9
Custom handler installed. Try pressing Ctrl+C (ignored for 5 seconds).
^CCurrently ignoring SIGINT...
Now SIGINT is being ignored completely for 5 seconds.
SIGINT restored to default. Press Ctrl+C to exit.
============================================================================
*/


