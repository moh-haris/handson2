#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefds[2];   // file descriptors for pipe
    char buffer[20];  // buffer for reading

    if (pipe(pipefds) == -1) {
        perror("pipe creation failed");
        return 1;
    }

    printf("Pipe created successfully!\n");

    const char *msg = "HELLO_PIPE\n";
    int len = strlen(msg) + 1;  // include null terminator

    // write into pipe
    if (write(pipefds[1], msg, len) == -1) {
        perror("write failed");
        return 1;
    }

    // read from pipe
    if (read(pipefds[0], buffer, sizeof(buffer)) == -1) {
        perror("read failed");
        return 1;
    }

    printf("Message read from pipe: %s", buffer);

    return 0;
}

