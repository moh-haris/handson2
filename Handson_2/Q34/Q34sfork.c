
/*
========================================================================================================
Name : Q34server
Author : Mohammed Haris
Description :  Write a program to create a concurrent server. 
a. use fork   
Date: 30 Sept, 2025.
========================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>

#define PORT 8080

void handle_client(int client_socket) {
    char buffer[1024] = {0};
    const char *response = "Hello from server";

    read(client_socket, buffer, sizeof(buffer));
    printf("Received from client: %s\n", buffer);

    send(client_socket, response, strlen(response), 0);
    printf("Response sent to client\n");

    close(client_socket);
    exit(0);  
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    signal(SIGCHLD, SIG_IGN);  //to prevent zombie processes

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;  // bind to all local interfaces
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {  //bind() tells the OS on which IP and port your server will accept connections.
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 5) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    while (1) {
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            continue;
        }

        if (fork() == 0) {  //step chld and parent created child handle this client handle and not accepting new client so it closes server fd
            close(server_fd);  
            handle_client(client_socket);
        } else {
            close(client_socket);   //parent closes client socket now parent can accept new clients
        }
    }

    close(server_fd);
    return 0;

    //every time a new client connects, the server forks a new process to handle that client. The child process handles the communication with the client, while the parent process goes back to listening for new connections. that is how concurrency is achieved using fork. server can handle multiple clients simultaneously, each in its own process.
}


/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q34$ gcc forkserver.c -o fork
haris@Haris:~/handson2/Q34$ ./fork
Server is listening on port 8080
client-1
Received from client: Hello from client
Response sent to client
client-2
Received from client: Hello from client
Response sent to client
============================================================================
*/
