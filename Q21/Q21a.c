#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    char buffer[100];
    int fd_write, fd_read;

    
    fd_write = open("fifo1", O_WRONLY);
    fd_read = open("fifo2", O_RDONLY);

    if (fd_write == -1 || fd_read == -1) {
        perror("open");
        exit(1);
    }

    while (1) {
        printf("Process1: Enter message: ");
        fgets(buffer, sizeof(buffer), stdin);

        write(fd_write, buffer, strlen(buffer) + 1);

        read(fd_read, buffer, sizeof(buffer));
        printf("Process1: Received reply: %s\n", buffer);
    }

    close(fd_write);
    close(fd_read);
    return 0;
}
