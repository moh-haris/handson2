

/*
============================================================================
Name : Q17
Author : Mohammed Haris
Description :  Write a program to execute ls -l | wc. 
a. use dup 
b. use dup2 
c. use fcntl
Date: 24th Sept, 2025.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe failed");
        exit(1);
    }

    /* We create a pipe using pipe(fd).
fd[1] is the write end and fd[0] is the read end.
After fork(), both child and parent have both ends of the pipe.

Child closes the read end (fd[0]), closes stdout, and uses dup(fd[1]) to make the write end of the pipe become the new stdout. Then child executes ls -l. As a result, ls -l writes its output into the pipe instead of the screen.

Parent closes the write end (fd[1]), closes stdin, and uses dup(fd[0]) to make the read end of the pipe become the new stdin. Then parent executes wc, which reads from the pipe the output produced by ls.

This creates: ls -l | wc manually using pipe, dup, fork, and execl.*/

    int option;
    printf("Select option:\n1. dup\n2. dup2\n3. fcntl\nChoice: ");
    scanf("%d", &option);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (option == 1) {
        if (pid == 0) {   
            close(fd[0]);
            close(STDOUT_FILENO);   
            dup(fd[1]);             
            execl("/bin/ls", "ls", "-l", NULL);
            perror("execl failed");
        } else {         
            close(fd[1]);
            close(STDIN_FILENO);    
            dup(fd[0]);            
            execl("/bin/wc", "wc", NULL);
            perror("execl failed");
        }
    }
    else if (option == 2) {
        if (pid == 0) {  
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);  
            execl("/bin/ls", "ls", "-l", NULL);
            perror("execl failed");
        } else {          
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);  
            execl("/bin/wc", "wc", NULL);
            perror("execl failed");
        }
    }
    else if (option == 3) {
        if (pid == 0) {  
            close(fd[0]);
            fcntl(fd[1], F_DUPFD, STDOUT_FILENO);
            execl("/bin/ls", "ls", "-l", NULL);
            perror("execl failed");
        } else {         
            close(fd[1]);
            fcntl(fd[0], F_DUPFD, STDIN_FILENO);  
            execl("/bin/wc", "wc", NULL);
            perror("execl failed");
        }
    }
    else {
        printf("Invalid option!\n");
    }

    return 0;
}

/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q17$ gcc Q17.c -o Q17
haris@Haris:~/handson2/Q17$ ./Q17
Select option:
1. dup
2. dup2
3. fcntl
Choice: 2
      3      20     107
============================================================================
*/


