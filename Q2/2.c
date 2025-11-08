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

haris@Haris:~/handson2/Q1$ gcc 1c.c -o 1c
haris@Haris:~/handson2/Q1$ ./1c
ITIMER_REAL fired!
ITIMER_REAL fired!
============================================================================
*/
