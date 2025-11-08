/*
========================================================================================================
Name : Q20read
Author : Mohammed Haris
Description :  Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 26 Oct, 2025.
========================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *fifo = "myfifo";  
    char buffer[100];

    int fd = open(fifo, O_RDONLY);
    if (fd == -1) {
        perror("open fifo");
        exit(1);
    }

    read(fd, buffer, sizeof(buffer));
    printf("Received message: %s\n", buffer);

    close(fd);
    return 0;
}

/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q20$ mkfifo myfifo
haris@Haris:~/handson2/Q20$ gcc Q20.c -o Q20r
haris@Haris:~/handson2/Q20$ ./Q20r
Received message: Hello Haris
============================================================================
*/

