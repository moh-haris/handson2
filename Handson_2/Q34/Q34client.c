
/*
========================================================================================================
Name : Q34client
Author : Mohammed Haris
Description :  Write a program to create a concurrent server. 
Date: 30 Sept, 2025.
========================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h> /*Use of this header file ✅ IP address conversion
✅ Network byte order ↔ Host byte order
✅ Internet operations (IPv4/IPv6)*/
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
    serv_addr.sin_port = htons(PORT); //hton is used to convert to network byte order to host byte order
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) { //pton is used to convert IP addresses from text to binary form
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

haris@Haris:~/handson2/Q33$ gcc Q34client.c -o client
haris@Haris:~/handson2/Q33$ ./client
Message sent to server
Received from server: Hello from server
============================================================================
*/







