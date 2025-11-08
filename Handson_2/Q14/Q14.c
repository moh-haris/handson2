
/*
============================================================================
Name : Q14
Author : Mohammed Haris
Description :  Write a simple program to create a pipe, write to the pipe, read from pipe and display on 
the monitor. 
Date: 24th Sept, 2025.
============================================================================
*/

// unnamed pipe it is for inter-process communication within the same process for same process half duplex read and write is blocking calls
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefds[2];   
    char buffer[20];  

    if (pipe(pipefds) == -1) {
        perror("pipe creation failed");
        return 1;
    }

    printf("Pipe created successfully!\n");

    const char *msg = "HELLO_HARIS\n";
    int len = strlen(msg) + 1;  

    
    if (write(pipefds[1], msg, len) == -1) { //default fd 0 is stdin 1 is stdout 2 is stderr
        perror("write failed");
        return 1;
    }

    if (read(pipefds[0], buffer, sizeof(buffer)) == -1) {
        perror("read failed");
        return 1;
    }

    printf("Message read from pipe: %s", buffer);

    return 0;
}

/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q14$ ./Q14
Pipe created successfully!
Message read from pipe: HELLO_PIPE
haris@Haris:~/handson2/Q14$
============================================================================
*/








