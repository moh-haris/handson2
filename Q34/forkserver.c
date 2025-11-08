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

    signal(SIGCHLD, SIG_IGN); 

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
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            continue;
        }

        if (fork() == 0) { 
            close(server_fd);  
            handle_client(client_socket);
        } else {
            close(client_socket);  
        }
    }

    close(server_fd);
    return 0;
}
