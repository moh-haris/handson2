#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigsegv(int sig) {
    printf("SIGSEGV caught (Segmentation Fault)\n");
    exit(1);
}

void handle_sigint(int sig) {
    printf("SIGINT caught! (Keyboard Interrupt)\n");
    exit(0);
}

void handle_sigfpe(int sig) {
    printf("SIGFPE caught! (Divide by zero / Floating-point exception)\n");
    exit(1);
}

int main() {
    struct sigaction sa_segv, sa_int, sa_fpe;


    sa_segv.sa_handler = handle_sigsegv;
    sigemptyset(&sa_segv.sa_mask);
    sa_segv.sa_flags = 0;
    sigaction(SIGSEGV, &sa_segv, NULL);

    sa_int.sa_handler = handle_sigint;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);

    sa_fpe.sa_handler = handle_sigfpe;
    sigemptyset(&sa_fpe.sa_mask);
    sa_fpe.sa_flags = 0;
    sigaction(SIGFPE, &sa_fpe, NULL);

    printf("Signal handlers installed. Try Ctrl+C, divide by zero, or segfault.\n");

    while (1) {
        printf("Press Ctrl+C to test SIGINT.\n");
        sleep(5);
        
       // int *p = NULL; *p = 5;   // SIGSEGV
         int x = 5 / 0;           // SIGFPE
    }

    return 0;
}
