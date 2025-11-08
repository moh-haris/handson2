/*
============================================================================
Name : Q2
Author : Mohammed Haris
Description : Write a program to print the system resource limits. Use getrlimit system call. 
Date: 19th Sept, 2025.
============================================================================
*/

#include <stdio.h>
#include <sys/resource.h>
#include <unistd.h>

void show_limit(int res, const char *desc) {
    struct rlimit lim;

    if (getrlimit(res, &lim) == 0) {
        printf("%-25s : Current = %ld, Maximum = %ld\n", desc, (long)lim.rlim_cur, (long)lim.rlim_max);
    } else {
        perror("getrlimit failed");
    }
}

int main() {
    show_limit(RLIMIT_CPU, "CPU time");
    show_limit(RLIMIT_FSIZE, "Maximum file size");
    show_limit(RLIMIT_DATA, "Data segment size");
    show_limit(RLIMIT_STACK, "Stack segment size");
    show_limit(RLIMIT_CORE, "Core file size");
    show_limit(RLIMIT_RSS, "Resident memory size");
    show_limit(RLIMIT_NPROC, "Max processes");
    show_limit(RLIMIT_NOFILE, "Max open files");

    return 0;
}

/*
============================================================================
OUTPUT 

haris@Haris:~/handson2/Q2$ vim 2.c
haris@Haris:~/handson2/Q2$ ./2
CPU time                  : Current = -1, Maximum = -1
Maximum file size         : Current = -1, Maximum = -1
Data segment size         : Current = -1, Maximum = -1
Stack segment size        : Current = 8388608, Maximum = -1
Core file size            : Current = 0, Maximum = -1
Resident memory size      : Current = -1, Maximum = -1
Max processes             : Current = 15281, Maximum = 15281
Max open files            : Current = 10240, Maximum = 1048576
============================================================================
*/