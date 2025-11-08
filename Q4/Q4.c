/*
============================================================================
Name : Q4
Author : Mohammed Haris
Description : Write a program to measure how much time is taken to execute 100 getppid ( )
system call. Use time stamp counter.
Date: 19th Sept, 2025.
============================================================================
*/

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

static inline uint64_t read_tsc()
{
    unsigned int low, high;
    __asm__ __volatile__(
        "rdtsc" : "=a"(low), "=d"(high));
    return ((uint64_t)high << 32) | low;
}

int main()
{
    uint64_t t1, t2;
    t1 = read_tsc();
    for (int k = 0; k < 100; k++)
    {
        getppid();
    }
    t2 = read_tsc();
    printf("CPU cycles taken = %llu\n", (unsigned long long)(t2 - t1));
    return 0;
}

/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q4$ gcc Q4.c -o 4
haris@Haris:~/handson2/Q4$ ./4
CPU cycles taken = 51870
============================================================================
*/
