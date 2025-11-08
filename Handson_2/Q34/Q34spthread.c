
/*
========================================================================================================
Name : Q34server
Author : Mohammed Haris
Description :  Write a program to create a concurrent server. 
b. use pthread_create   
Date: 30 Sept, 2025.
========================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#define PORT 8080

void* handle_client(void* arg) {
    int client_socket = *(int*)arg;
    free(arg);

    char buffer[1024] = {0};
    const char *response = "Hello from server";

    read(client_socket, buffer, sizeof(buffer));
    printf("Received from client: %s\n", buffer);

    send(client_socket, response, strlen(response), 0);
    printf("Response sent to client\n");

    close(client_socket);
    pthread_exit(NULL);
}

int main() {
    int server_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

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

    if (listen(server_fd, 5) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    while (1) {
        int *client_socket = malloc(sizeof(int)); //if we use int it will create variable in stack memory and will be lost after each iteration
         //so we use malloc to allocate memory in heap so after iteration mem remain valid
         //remember to free the memory in handle_client function 
        if ((*client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            free(client_socket);
            continue;
        }

        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, client_socket);
        pthread_detach(tid); 
    }

    close(server_fd);
    return 0;
}


/*
============================================================================
OUTPUT

haris@Haris:~/handson2/Q34$ gcc pthreadserver.c -o pthread -lpthread
haris@Haris:~/handson2/Q34$ ./pthread
Server is listening on port 8080
client-1
Received from client: Hello from client
Response sent to client
client-2
Received from client: Hello from client
Response sent to client
============================================================================
*/
