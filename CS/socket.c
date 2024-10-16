//Load the wanted libraries for socket program.
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>//htons function in C.

//Proceed to main function.
int main()
{
    //let's declare the wanted variable for a socket.
    //Create a socket variable to store server socket value in it.
    int server_socket; //used for creating socket.
    int client_socket; //used for accepting connection.

    //Decalred a structure to proceed for network operations.
    struct sockaddr_in server_addr; // Structure required by bind.
    //create a buffer variable to store the response for server.
    //Once client accept the connection the below msg can be able to notice.
    char buffer[500] = "Hello I'm Server Talking!!"; //This buffer for send the data to client.
    char buffer2[700]; //this buffer for receive the data.

    //Now let's create socket object
    //socket function take 3 arguments 
    //1st ip family > AF_INET(Ipv4)
    //2nd Conection stream > TCP (SOCK_STREAM) > For using other sockets like udp can proceed to > UDP (SOCK_DGGRAM)
    //3rd NULL > 0 > To specify the end.
    server_socket = socket(AF_INET, SOCK_STREAM, 0); //Creates a TCP socket.

    //Specify the information for the specified structure above.
    server_addr.sin_family = AF_INET; //Declaring Type
    server_addr.sin_port = htons(4445); //Decalring port
    server_addr.sin_addr.s_addr = inet_addr("192.168.1.52"); //Declaring host address

    //Now will move to the bind function.
    //bind function take 3 arguments
    //server socket that we craeted.
    //map the pointer to the structure that we declared
    //size of the structure.
    bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)); //Bind the server.

    //Now listen for the connection
    //listen function take 2 arguments > socket that we created and the number of connection
    listen(server_socket, 5);

    //Now will store the accept connection to the client socket
    //accept function take 3 arguments.
    client_socket = accept(server_socket, NULL, NULL); //accept incoming connection
    //Let's ensure that the client was connected to the server.
    printf("Client Connected With Server.\n");

    //After the accptance was successful implement send and recv data.
    send(client_socket, buffer, sizeof(buffer), 0); //send data
    recv(client_socket, buffer2, sizeof(buffer2), 0); //recv data

    //Send and recv function takes same parameters as input > client socket, sending buffer name or receving buffer name and size of buffer and final flag is set to zero.

    //Print the client sending messages
    printf("Client Sent : %s", buffer2);
    //close the connection. Terminate the session.
    close(server_socket);
    return 0;

}
