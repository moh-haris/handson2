
/*
========================================================================================================
Name : Q33client
Author : Mohammed Haris
Description :  Write a program to communicate between two machines using socket.    
Date: 30 Sept, 2025.
========================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    const char *message = "Hello from client";
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address / Address not supported");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        exit(EXIT_FAILURE);
    }
    send(sock, message, strlen(message), 0);
    printf("Message sent to server\n");
    read(sock, buffer, sizeof(buffer));
    printf("Received from server: %s\n", buffer);
    close(sock);
    return 0;
}

/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q33$ gcc Q33client.c -o client
haris@Haris:~/handson2/Q33$ ./client
Message sent to server
Received from server: Hello from server
============================================================================
*/







