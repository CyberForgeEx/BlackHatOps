# Remote Process Injection - Shellcode

This directory contains a C program demonstrating remote process injection of shellcode, part of the **BlackHatOps** repository. The program is designed for **educational and research purposes** in offensive security, showcasing how shellcode can be injected into a remote process on a **Windows** system. This README provides an overview of the code, explains the processes involved, and includes compilation and usage instructions.

## Overview

The Remote Process Injection program (`rpi.c`) illustrates how to inject shellcode into the address space of a target process and execute it remotely. This technique is commonly used in security research to understand process manipulation and code execution in controlled environments. The program targets Windows systems and uses Windows API functions to perform the injection.

## Files

- `rpi.c`: Implements the logic for injecting shellcode into a remote process and executing it.

## Process Explanation

### rpi.c (Windows)

1. **Shellcode Preparation**:
   - The program defines a sample shellcode array with the reverse shell payload(_Shellcode_).
   - Shellcode is raw machine code that will be injected and executed in the target process.

2. **Open Target Process**:
   - The `OpenProcess()` function is used to obtain a handle to the target process, identified by its Process ID (PID).
   - The program requires sufficient permissions (e.g., `PROCESS_ALL_ACCESS`) to manipulate the target process.

3. **Allocate Memory in Target Process**:
   - `VirtualAllocEx()` allocates a region of memory in the target process’s address space with executable permissions (`PAGE_EXECUTE_READWRITE`).
   - This memory region will hold the shellcode.

4. **Write Shellcode to Target Process**:
   - `WriteProcessMemory()` copies the shellcode from the injector’s memory to the allocated memory in the target process.

5. **Execute Shellcode**:
   - `CreateRemoteThread()` creates a new thread in the target process, with the thread’s entry point set to the address of the injected shellcode.
   - This causes the shellcode to execute within the context of the target process.

6. **Cleanup**:
   - The program closes handles to the target process and thread using `CloseHandle()` to prevent resource leaks.

### Key Concepts

- **Shellcode**: Position-independent machine code that performs a specific task (e.g., displaying a message box or executing a command).
- **Process Injection**: A technique to execute code in another process’s address space, often used in malware analysis or penetration testing.
- **Windows API**: Functions like `OpenProcess`, `VirtualAllocEx`, `WriteProcessMemory`, and `CreateRemoteThread` are used for process manipulation.
- **Permissions**: The injector requires administrative privileges to access and modify the target process.

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/CyberForgeEx/BlackHatOps.git
   ```
2. Navigate to the Remote Process Injection directory:
   ```bash
   cd BlackHatOps/Basic\ Concepts/Remote\ Process\ Injection\ -\ Shellcode
   ```

## Compilation

### Windows
1. Open a terminal (e.g., MSYS2 MinGW 64-bit, Git Bash, or PowerShell with MinGW in PATH).
2. Compile the program:
   ```bash
   gcc -o inject rpi.c
   ```

## Usage

1. **Identify Target Process**:
   - Determine the PID of the target process (e.g., using Task Manager or `tasklist` in Command Prompt).
   - Example: `tasklist | findstr [process]` to find the PID of the target process.

2. **Run the Injector**:
   - Execute the compiled binary, passing the target PID as a command-line argument:
     ```bash
     ./inject.exe <PID>
     ```
   - Example: `./inject.exe 1234` (replace `1234` with the actual PID).
   - The program injects the shellcode into the target process, which executes it (e.g., displaying a MessageBox).

3. **Output**:
   - The shellcode stashed and executes in the target process (e.g., a MessageBox appears).

## Troubleshooting

- **“gcc is not recognized”**: Ensure MinGW/MSYS2 is installed and added to PATH.
- **“OpenProcess failed”**: Verify the PID is valid and the program is run with administrative privileges (right-click terminal and select “Run as Administrator”).
- **“Access denied”**: Ensure the target process is accessible and the injector has sufficient permissions.
- **Shellcode fails to execute**: Check the shellcode for correctness and ensure it’s compatible with the target process’s architecture (e.g., 32-bit vs. 64-bit).
- **Turn off windows defender**: Current version off my code caught by Windows defender when injecting shellcode into the legitimate process ID.

## Disclaimer

This program is for **educational and research purposes only**. Use it only on systems you own or have explicit permission to test. Unauthorized use, including injecting code into processes without consent, is **illegal and unethical**. The developers are not responsible for misuse or damages. Always comply with local laws and regulations.
