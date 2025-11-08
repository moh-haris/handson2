#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
    struct sigaction ignore_act, default_act;


    ignore_act.sa_handler = SIG_IGN;
    sigemptyset(&ignore_act.sa_mask);
    ignore_act.sa_flags = 0;

   
    default_act.sa_handler = SIG_DFL;
    sigemptyset(&default_act.sa_mask);
    default_act.sa_flags = 0;

  
    if (sigaction(SIGINT, &ignore_act, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }
    printf("SIGINT is ignored for 5 seconds. Press Ctrl+C \n");
    sleep(5);

   
    if (sigaction(SIGINT, &default_act, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }
    printf("SIGINT restored to default. Press Ctrl+C to terminate the program.\n");

   
    while (1) {
        pause(); 
    }

    return 0;
}
