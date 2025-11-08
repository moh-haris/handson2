/*
========================================================================================================
Name : Q19b
Author : Mohammed Haris
Description : Create a FIFO file by
a. mknod command
b. mkfifo command
c. use strace command to find out, which command (mknod or mkfifo) is better.
d. mknod system call
e. mkfifo library function
Date: 26 Oct, 2025.
========================================================================================================
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    mknod("fifo3", S_IFIFO | 0666, 0);
    mkfifo("fifo4", 0666);
    return 0;
}


/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q19$ gcc Q19.c -o Q19d
haris@Haris:~/handson2/Q19$ strace ./Q19d


============================================================================
*/

