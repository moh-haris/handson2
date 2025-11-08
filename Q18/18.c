#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

void segv_handler(int sig) {
    printf("Caught SIGSEGV (Segmentation fault)\n");
    exit(0);
}

void int_handler(int sig) {
    printf("Caught SIGINT (Ctrl+C)\n");
    exit(0);
}

void fpe_handler(int sig) {
    printf("Caught SIGFPE (Floating point exception)\n");
    exit(0);
}

void alarm_handler(int sig) {
    printf("Caught signal %d (Timer/Alarm)\n", sig);
}

int main() {
    int choice;
    printf("Choose an option:\n"
           "1. SIGSEGV\n"
           "2. SIGINT\n"
           "3. SIGFPE\n"
           "4. SIGALRM (alarm)\n"
           "5. SIGALRM (setitimer ITIMER_REAL)\n"
           "6. SIGVTALRM (setitimer ITIMER_VIRTUAL)\n"
           "7. SIGPROF (setitimer ITIMER_PROF)\n=> ");
    scanf("%d", &choice);

    struct itimerval timer = {{2, 0}, {2, 0}};  // interval + initial value

    switch (choice) {
        case 1: {  // SIGSEGV
            signal(SIGSEGV, segv_handler);
            char *ptr = NULL;
            *ptr = 'A';  // force segmentation fault
            break;
        }
        case 2: {  // SIGINT
            signal(SIGINT, int_handler);
            printf("Press Ctrl+C within 5 seconds...\n");
            sleep(5);
            break;
        }
        case 3: {  // SIGFPE
            signal(SIGFPE, fpe_handler);
            int x = 5, y = 0;
            printf("Result = %d\n", x / y);  // force divide by zero
            break;
        }
        case 4: {  // SIGALRM with alarm()
            signal(SIGALRM, alarm_handler);
            
                alarm(2);
                pause();  // wait for signal instead of busy sleep
            
            break;
        }
        case 5: {  // SIGALRM with setitimer()
            signal(SIGALRM, alarm_handler);
            setitimer(ITIMER_REAL, &timer, NULL);
            while (1) pause();
            break;
        }
        case 6: {  // SIGVTALRM
            signal(SIGVTALRM, alarm_handler);
            setitimer(ITIMER_VIRTUAL, &timer, NULL);
            while (1);  // consume CPU to trigger virtual timer
            break;
        }
        case 7: {  // SIGPROF
            signal(SIGPROF, alarm_handler);
            setitimer(ITIMER_PROF, &timer, NULL);
            while (1);  // keep CPU busy
            break;
        }
        default:
            printf("Invalid choice.\n");
            break;
    }

    return 0;
}

