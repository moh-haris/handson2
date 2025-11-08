#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *name_fifo = "fifo_call";
    if (mknod(name_fifo, S_IFIFO | 0666, 0) == -1) {
        perror("mknod");
        exit(EXIT_FAILURE);
    }
    printf("FIFO created using mknod() system call: %s\n", name_fifo);
    return 0;
}
