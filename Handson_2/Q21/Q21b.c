
/*
========================================================================================================
Name : Q21b
Author : Mohammed Haris
Description :  Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 26 Oct, 2025.
========================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    char buffer[100];
    int fd_write, fd_read;

    
    fd_read = open("fifo1", O_RDONLY);
    fd_write = open("fifo2", O_WRONLY);

    if (fd_write == -1 || fd_read == -1) {
        perror("open");
        exit(1);
    }

    while (1) {
        read(fd_read, buffer, sizeof(buffer));
        printf("Process2: Received: %s\n", buffer);

        printf("Process2: Enter reply: ");
        fgets(buffer, sizeof(buffer), stdin);

        write(fd_write, buffer, strlen(buffer) + 1);
    }

    close(fd_write);
    close(fd_read);
    return 0;
}


/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q21$ ./q21b
Process2: Received: Hello

Process2: Enter reply: yes hello
Process2: Received: yes hello

Process2: Enter reply:
============================================================================
*/


