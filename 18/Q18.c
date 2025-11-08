/*
========================================================================================================
Name : 18.c
Author : Mohammed Haris
Description : . Write a program to find out total number of directories on the pwd. 
execute ls -l | grep ^d | wc ? Use only dup2.
Date: 25th Sept, 2025.
========================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int p1[2], p2[2];
    pid_t pid1, pid2, pid3;
    if (pipe(p1) == -1) { perror("p1"); exit(1); }
    if (pipe(p2) == -1) { perror("p2"); exit(1); }
    pid1 = fork();
    if (pid1 == 0) {
        
        dup2(p1[1], STDOUT_FILENO);
        close(p1[0]); close(p1[1]);
        close(p2[0]); close(p2[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls"); exit(1);
    }
    pid2 = fork();
    if (pid2 == 0) {
        
        dup2(p1[0], STDIN_FILENO);
        dup2(p2[1], STDOUT_FILENO);

        close(p1[0]); close(p1[1]);
        close(p2[0]); close(p2[1]);

        execlp("grep", "grep", "^d", NULL);
        perror("execlp grep"); exit(1);
    }

    pid3 = fork();
    if (pid3 == 0) {

        dup2(p2[0], STDIN_FILENO);

        close(p1[0]); close(p1[1]);
        close(p2[0]); close(p2[1]);

        execlp("wc", "wc", NULL);
        perror("execlp wc"); exit(1);
    }

    close(p1[0]); 
    close(p1[1]);
    close(p2[0]); 
    close(p2[1]);
    wait(NULL);
    wait(NULL);
    wait(NULL);

    return 0;
}


/*
============================================================================
OUTPUT

haris@Haris:~/handson2/18$ gcc Q18.c -o Q18
haris@Haris:~/handson2/18$ ./Q18
      0       0       0
haris@Haris:~/handson2/18$ ls -l | grep ^d | wc
      0       0       0
============================================================================
*/
