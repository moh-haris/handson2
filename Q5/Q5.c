
/*
============================================================================
Name : Q5
Author :  Write a program to print the system limitation of  
       a. maximum length of the arguments to the exec family of functions.  
       b. maximum number of simultaneous process per user id.  
       c. number of clock ticks (jiffy) per second.  
       d. maximum number of open files 
       e. size of a page 
       f. total number of pages in the physical memory 
       g. number of currently available pages in the physical memory.  
Date: 23th Sept, 2025.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>

int main() {
    
    printf("System Configuration Limits\n");
    
    long max_arg_length = sysconf(_SC_ARG_MAX);
    printf("1-Max argument list size for exec: %ld bytes\n", max_arg_length);

    long max_child_processes = sysconf(_SC_CHILD_MAX);
    printf("2-Maximum simultaneous processes per user ID: %ld\n", max_child_processes);

   long clock_ticks_per_sec = sysconf(_SC_CLK_TCK);
    printf("3-Clock ticks per second HZ: %ld\n", clock_ticks_per_sec);

    long max_open_file_handles = sysconf(_SC_OPEN_MAX);
    printf("4-System-wide limit for open files FD: %ld\n", max_open_file_handles);

   long memory_page_size = sysconf(_SC_PAGESIZE);
    printf("5-System memory page size: %ld bytes\n", memory_page_size);

   long total_physical_pages = sysconf(_SC_PHYS_PAGES);
    printf("6-Total pages in physical memory: %ld\n", total_physical_pages);

    long available_physical_pages = sysconf(_SC_AVPHYS_PAGES);
    printf("7-Currently available physical memory pages: %ld\n", available_physical_pages);
    
   
    if (memory_page_size > 0 && available_physical_pages > 0) {
        printf("(Estimated available memory: %ld bytes)\n", available_physical_pages * memory_page_size);
    }

    return 0;
}

/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q5$ gcc Q5.c -o Q5
haris@Haris:~/handson2/Q5$ ./Q5
System Configuration Limits
1-Max argument list size for exec: 2097152 bytes
2-Maximum simultaneous processes per user ID: 15281
3-Clock ticks per second HZ: 100
4-System-wide limit for open files FD: 10240
5-System memory page size: 4096 bytes
6-Total pages in physical memory: 980536
7-Currently available physical memory pages: 841109
(Estimated available memory: 3445182464 bytes)
============================================================================
*/

