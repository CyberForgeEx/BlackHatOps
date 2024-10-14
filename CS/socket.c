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
    char buffer[500] = "Hello I'm Server Talking!!"; 

    //Now let's create socket object
    //socket function take 3 arguments 
    //1st ip family > AF_INET(Ipv4)
    //2nd Conection stream > TCP (SOCK_STREAM) > For using other sockets like udp can proceed to > UDP (SOCK_DGGRAM)
    //3rd NULL > 0 > To specify the end.
    server_socket = socket(AF_INET, SOCK_STREAM, 0); //Creates a TCP socket.

    //Specify the information for the specified structure above.
    server_addr.sin_family = AF_INET; //Declaring Type
    server_addr.sin_port = htons(4445); //Decalring port
    server_addr.sin_addr.s_addr = inet_addr("10.0.4.76"); //Declaring host address

    //Now will move to the bind function.
    //bind function take 3 arguments
    //server socket that we craeted.
    //map the pointer to the structure that we declared
    //size of the structure.
    bind(server_socket, (struct server_addr*) &server_addr, sizeof(server_addr)); //Bind the server.






}
