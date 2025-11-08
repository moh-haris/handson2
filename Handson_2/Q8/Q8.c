/*
============================================================================
Name : Q8
Author : Mohammed Haris
Description :  Write a separate program using signal system call to catch the following signals. 
   a. SIGSEGV 
   b. SIGINT 
   c. SIGFPE 
   d. SIGALRM (use alarm system call) 
   e. SIGALRM (use setitimer system call) 
   f. SIGVTALRM (use setitimer system call) 
   g. SIGPROF (use setitimer system call) 
Date: 23th Sept, 2025.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

void handler(int sig) {
    switch(sig) {
        case SIGSEGV:   printf("Caught SIGSEGV (Segmentation Fault)\n"); break;
        case SIGINT:    printf("Caught SIGINT (Ctrl+C)\n"); break;
        case SIGFPE:    printf("Caught SIGFPE (Divide by Zero)\n"); break;
        case SIGALRM:   printf("Caught SIGALRM (Timer/Alarm)\n"); break;
        case SIGVTALRM: printf("Caught SIGVTALRM (Virtual Timer)\n"); break;
        case SIGPROF:   printf("Caught SIGPROF (Profiling Timer)\n"); break;
        default:        printf("Caught signal %d\n", sig);
    }
    exit(0);
}

int main() {
    int choice;
    struct itimerval timer;

    
    signal(SIGSEGV, handler);
    signal(SIGINT, handler);
    signal(SIGFPE, handler);
    signal(SIGALRM, handler);
    signal(SIGVTALRM, handler);
    signal(SIGPROF, handler);

    printf("Choose a signal to demonstrate:\n");
    printf("1. SIGSEGV (Segmentation Fault)\n");
    printf("2. SIGINT  (Press Ctrl+C)\n");
    printf("3. SIGFPE  (Divide by Zero)\n");
    printf("4. SIGALRM using alarm()\n");
    printf("5. SIGALRM using setitimer()\n");
    printf("6. SIGVTALRM using setitimer()\n");
    printf("7. SIGPROF using setitimer()\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1: {
            int *p = NULL;
            *p = 10;   
            break;
        }
        case 2: {
            printf("Press Ctrl+C to trigger SIGINT\n");
            while(1) sleep(1);
            break;
        }
        case 3: {
            int x = 5 / 0;   
            (void)x;
            break;
        }
        case 4: {
            alarm(3);   
            printf("Waiting for SIGALRM (alarm)\n");
            pause();
            break;
        }
        case 5: {
            timer.it_value.tv_sec = 2;
            timer.it_value.tv_usec = 0;
            timer.it_interval.tv_sec = 0;
            timer.it_interval.tv_usec = 0;
            setitimer(ITIMER_REAL, &timer, NULL);
            printf("Waiting for SIGALRM (setitimer)\n");
            pause();
            break;
        }
        case 6: {
            timer.it_value.tv_sec = 1;
            timer.it_value.tv_usec = 0;
            timer.it_interval.tv_sec = 0;
            timer.it_interval.tv_usec = 0;
            setitimer(ITIMER_VIRTUAL, &timer, NULL);
            printf("Busy loop waiting for SIGVTALRM\n");
            while(1);   
            break;
        }
        case 7: {
            timer.it_value.tv_sec = 1;
            timer.it_value.tv_usec = 0;
            timer.it_interval.tv_sec = 0;
            timer.it_interval.tv_usec = 0;
            setitimer(ITIMER_PROF, &timer, NULL);
            printf("Busy loop waiting for SIGPROF\n");
            while(1);   
            break;
        }
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}

/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q8$ ./Q8
Choose a signal to demonstrate:
1. SIGSEGV (Segmentation Fault)
2. SIGINT  (Press Ctrl+C)
3. SIGFPE  (Divide by Zero)
4. SIGALRM using alarm()
5. SIGALRM using setitimer()
6. SIGVTALRM using setitimer()
7. SIGPROF using setitimer()
Enter choice: 3
Caught SIGFPE (Divide by Zero)
============================================================================
*/

