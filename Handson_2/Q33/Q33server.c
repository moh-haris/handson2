
/*
========================================================================================================
Name : Q33server
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
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char *response = "Hello from server";

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Server is listening on port %d\n", PORT);

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    read(new_socket, buffer, sizeof(buffer));
    printf("Received from client: %s\n", buffer);

    send(new_socket, response, strlen(response), 0);
    printf("Response sent to client\n");

    close(new_socket);
    close(server_fd);

    return 0;
}

/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q33$ gcc Q33server.c -o server
haris@Haris:~/handson2/Q33$ ./server
Server is listening on port 8080
Received from client: Hello from client
Response sent to client
============================================================================
*/







