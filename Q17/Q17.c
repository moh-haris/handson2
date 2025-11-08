
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

haris@Haris:~/handson2/Q16$ gcc Q16.c -o Q16
haris@Haris:~/handson2/Q16$ ./Q16
Child: sending 111 to parent
Parent: got 111 from child
Parent: sending 222 to child
Child: received 222 from parent
============================================================================
*/



