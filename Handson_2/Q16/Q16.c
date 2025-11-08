
/*
============================================================================
Name : Q16
Author : Mohammed Haris
Description : Write a program to send and receive data from parent to child vice versa. Use two way 
communication. 
Date: 24th Sept, 2025.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int pipe_pc[2]; 
    int pipe_cp[2]; 

    if (pipe(pipe_pc) == -1 || pipe(pipe_cp) == -1) {
        perror("pipe creation failed");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }
    else if (pid == 0) {    //chiled process
        close(pipe_cp[0]);  //by default fd=0 is for read and fd=1 is for write
        close(pipe_pc[1]);   

        int sendData = 111;
        printf("Child: sending %d to parent\n", sendData);
        write(pipe_cp[1], &sendData, sizeof(sendData)); //first chiled send write from cp

        int recvData = 0;
        read(pipe_pc[0], &recvData, sizeof(recvData));
        printf("Child: received %d from parent\n", recvData); //child read from pc

        close(pipe_cp[1]);
        close(pipe_pc[0]);
    }
    else {   
        close(pipe_cp[1]);   
        close(pipe_pc[0]);  

        int received = 0;
        read(pipe_cp[0], &received, sizeof(received)); //parent read from cp
        printf("Parent: got %d from child\n", received);

        int sendValue = 222;
        printf("Parent: sending %d to child\n", sendValue);
        write(pipe_pc[1], &sendValue, sizeof(sendValue)); //then parent send data from pc

        close(pipe_cp[0]);
        close(pipe_pc[1]);
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

