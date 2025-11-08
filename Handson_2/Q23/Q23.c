/*
========================================================================================================
Name : Q23
Author : Mohammed Haris
Description :  . Write a program to print the maximum number of files can be opened within a process and  
size of a pipe (circular buffer). 
Date: 27 Oct, 2025.
========================================================================================================
*/

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

/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q23$ gcc Q23.c -o Q23
haris@Haris:~/handson2/Q23$ ./Q23
Size of pipe is = 4096 bytes
Maximum number of files that can be opened = 10240
============================================================================
*/



