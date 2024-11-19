
/* client.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE] = {0};

    // Create socket
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // Convert IP address from text to binary
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server. Type your message (or 'quit' to exit):\n");

    while (1) {
        printf("> ");
        fgets(buffer, BUFFER_SIZE, stdin);
        
        // Remove newline
        buffer[strcspn(buffer, "\n")] = 0;

        // Check for quit command
        if (strcmp(buffer, "quit") == 0) {
            break;
        }

        // Send message
        send(sock_fd, buffer, strlen(buffer), 0);

        // Receive echo
        memset(buffer, 0, BUFFER_SIZE);
        recv(sock_fd, buffer, BUFFER_SIZE, 0);
        
        printf("Server echo: %s\n", buffer);
    }

    close(sock_fd);
    return 0;
}