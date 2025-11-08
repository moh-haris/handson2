/*
========================================================================================================
Name : Q19
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
    return mknod("fifo1", S_IFIFO | 0666, 0);
}


/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q19$ gcc Q19.c -o Q19
haris@Haris:~/handson2/Q19$ ./Q19


============================================================================
*/

