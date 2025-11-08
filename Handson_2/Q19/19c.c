/*
========================================================================================================
Name : Q19c
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

#include <stdlib.h>

int main() {
    system("mknod test1 p");
    system("mkfifo test2");
    return 0;
}



/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q19$ gcc Q19.c -o Q19c
haris@Haris:~/handson2/Q19$ strace ./Q19c


============================================================================
*/

