//Implementation of the port scanner in future perspective.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

// Function to check if a port is open
int check_port(char *ip, int port) {
    int sock;
    struct sockaddr_in target;
    
    // Create a socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return 0;
    }

    // Set up the target address and port
    target.sin_family = AF_INET;
    target.sin_port = htons(port);
    target.sin_addr.s_addr = inet_addr(ip);

    // Try to connect to the port
    int result = connect(sock, (struct sockaddr *)&target, sizeof(target));
    
    close(sock);
    
    // Return if the port is open or closed
    return result == 0 ? 1 : 0;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <IP> <start_port> <end_port>\n", argv[0]);
        return 1;
    }

    char *ip = argv[1];
    int start_port = atoi(argv[2]);
    int end_port = atoi(argv[3]);

    printf("Scanning IP: %s, Ports: %d-%d\n", ip, start_port, end_port);
    
    for (int port = start_port; port <= end_port; port++) {
        if (check_port(ip, port)) {
            printf("Port %d is open\n", port);
        } else {
            printf("Port %d is closed\n", port);
        }
    }

    return 0;
}
