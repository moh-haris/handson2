/*
========================================================================================================
Name : Q20writer
Author : Mohammed Haris
Description :  Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 26 Oct, 2025.
========================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char *fifo = "myfifo";  // Updated FIFO name
    char message[100];

    int fd = open(fifo, O_WRONLY);
    if (fd == -1) {
        perror("open fifo");
        exit(1);
    }

    printf("Enter message to send: ");
    fgets(message, sizeof(message), stdin);

    write(fd, message, strlen(message)+1);
    printf("Message sent!\n");

    close(fd);
    return 0;
}

/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q20$ ./Q20w
Enter message to send: Hello Haris
Message sent!
============================================================================
*/


