# **(BlackHatOps) Offensive Operations Provider - Using C.**

###### Objective of the program - Offensive connection implementation in the target machine. (Target : Windows)

- Create a connection with server (Socket Program)

- Create a Stealth Shell function (Entry Point)

- Automatically Start Program when target machine reboot (Persistence) => Windows Registery Editor.

- Start / Stop Other Programs and services in the target. (Process Administration)

- Navigating through different directories. (Directory Transversal)

- Implementing a key logger in the backdoor. (Record keystrokes). => Additional Concept.

- Command to execute the server > "gcc [server program] -o <executable name>"

- Command to execute the backdoor > "i686-w64-mingw32-gcc -o <executable name> [progarm Name]  -lwsock32 -lwininet"  
