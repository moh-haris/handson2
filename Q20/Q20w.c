#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char *fifo = "myfifo"; 
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
