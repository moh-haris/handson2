#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    long pipe_size, max_files;
    pipe_size = pathconf(".", _PC_PIPE_BUF);
    if (pipe_size == -1) {
        perror("pathconf");
        exit(1);
    }
    max_files = sysconf(_SC_OPEN_MAX);
    if (max_files == -1) {
        perror("sysconf");
        exit(1);
    }

    printf("Size of pipe is = %ld bytes\n", pipe_size);
    printf("Maximum number of files that can be opened = %ld\n", max_files);

    return 0;
}
