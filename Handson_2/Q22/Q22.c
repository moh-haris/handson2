/*
========================================================================================================
Name : Q22
Author : Mohammed Haris
Description :  . Write a program to wait for data to be written into FIFO within 10 seconds, use select 
system call with FIFO.
Date: 27 Oct, 2025.
========================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define FIFO_NAME "myfifo"

int main() {
    int fd;
    fd_set readfds;
    struct timeval timeout;
    char buffer[256];
    int ret, n;

    if (mkfifo(FIFO_NAME, 0666) == -1) {
        if (errno != EEXIST) {
            perror("mkfifo");
            exit(EXIT_FAILURE);
        }
    }

    printf("Opening FIFO for reading...\n");
    fd = open(FIFO_NAME, O_RDONLY | O_NONBLOCK);  
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }


    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);

    
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    printf("Waiting for data\n");

   
    ret = select(fd + 1, &readfds, NULL, NULL, &timeout);

    if (ret == -1) {
        perror("select");
        close(fd);
        exit(EXIT_FAILURE);
    } else if (ret == 0) {
        printf("Timeout: No data within 10 seconds.\n");
    } else {
        if (FD_ISSET(fd, &readfds)) {
            n = read(fd, buffer, sizeof(buffer) - 1);
            if (n > 0) {
                buffer[n] = '\0';
                printf("Received: %s\n", buffer);
            } else {
                printf("No data read (FIFO closed by writer).\n");
            }
        }
    }

    close(fd);
    unlink(FIFO_NAME); 
    return 0;
}

/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q22$ gcc Q22.c -o Q22
haris@Haris:~/handson2/Q22$ ./Q22
Opening FIFO for reading...
Waiting for data
haris@Haris:~/handson2/Q22$ echo "Hello" > myfifo
Received: Hello
============================================================================
*/



