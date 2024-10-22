//Client is windows OS
//Let's load the neccessary libraries want to smooth execution of the code.
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

//Add the pragma comment
//this directive used to link the library to the linker.
#pragma comment(lib, "ws2_32.lib")

//Entry Point
int main()
{
    //first step is initializing the win socket.
    //for the socket operation in windows want to create WSAdata structure.
    SOCKET client_soc; // craate socket structure
    WSADATA wsastructure; //create a WSAdata structure. for strup function initialization.
    int result; //save the socket result.

    //Now will specify the receive and response buffer
    char reiceve[500];
    char response[500] = "Hello I'm the client";

    //create a structure for client addr to specify connection option.
    struct sockaddr_in client_addr; //Structure required by connect.

    result = WSAStartup(MAKEWORD(2, 2), &wsastructure); //Initialization of winsock occurs here the result is store that.
    if (result != 0)
    {
        printf("[!] Winsock Initilization Failed\n");
        return 1;
    }

    //create the socket
    client_soc = socket(AF_INET, SOCK_STREAM, 0);

    //Now, specify the network details below
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(4445);
    client_addr.sin_addr.s_addr = inet_addr("192.168.1.52");

    //Now will implement conncet function.
    connect(client_soc, (SOCKADDR*) &client_addr, sizeof(client_addr));

    //After connecting can be able to reiceve data.
    //before sending the data from the client want to recv the response from the serverafter that send the response to the server.
    recv(client_soc, reiceve, sizeof(reiceve), 0); //receive the acknowledge
    printf("Data From The Server : %s\n", reiceve); //print the reply from the server

    //now will implement send the data
    send(client_soc, response, sizeof(response), 0);

    //Close and clean the socket.
    closesocket(client_soc);
    WSACleanup();
    return 0;



}
