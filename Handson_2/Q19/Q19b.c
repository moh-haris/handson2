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

int main() {
    return mkfifo("fifo2", 0666);
}


/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q19$ gcc Q19.c -o Q19b
haris@Haris:~/handson2/Q19$ ./Q19b

============================================================================
*/