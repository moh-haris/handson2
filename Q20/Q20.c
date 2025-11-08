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
