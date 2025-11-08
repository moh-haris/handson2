/*
============================================================================
Name : Q3
Author : Mohammed Haris
Description :Write a program to set (any one) system resource limit. Use setrlimit system call.  
Date: 19th Sept, 2025.
============================================================================
*/

#include <stdio.h>
#include <sys/resource.h>
#include <unistd.h>

int main() {
    struct rlimit rl;

    

        if (getrlimit(RLIMIT_CPU, &rl) == 0) {
            printf("CPU time limit before update:\n");
            printf("  Soft = %ld seconds, Hard = %ld seconds\n", (long)rl.rlim_cur, (long)rl.rlim_max);
        } else {
            perror("getrlimit failed");
        }

    rl.rlim_cur = 5;   
    rl.rlim_max = 10;  

     if (setrlimit(RLIMIT_CPU, &rl) == 0) {
        printf("CPU time limit after update:\n");
        printf("  Soft = %ld seconds, Hard = %ld seconds\n", (long)rl.rlim_cur, (long)rl.rlim_max);
    } else {
        perror("setrlimit failed");
    }

    return 0;
}


/*
============================================================================
OUTPUT 

haris@Haris:~/handson2/Q3$ ./3
CPU time limit before update:
  Soft = -1 seconds, Hard = -1 seconds
CPU time limit after update:
  Soft = 5 seconds, Hard = 10 seconds
CPU time limit exceeded (core dumped)
============================================================================
*/