# BlackHatOps - Offensive Operations Provider

**BlackHatOps** is a proof-of-concept offensive security tool developed in C, designed to demonstratepenetration testing techniques on Windows systems. This program implements a backdoor with various malicious capabilities for educational and research purposes only.

**⚠️ Disclaimer**: This project is intended for authorized security testing and educational purposes. Unauthorized use on systems you do not own or have explicit permission to test is illegal and unethical. Use responsibly and within legal boundaries.

## Objective

The primary objective of this project is to establish an reverse connection on a target Windows machine, enabling remote control and persistence for security testing purposes.

## Features

- **Remote Connection**: Establishes a connection to a remote server using socket programming.
- **Stealth Shell**: Creates a hidden shell as the entry point for remote command execution.
- **Persistence**: Ensures the program automatically starts upon system reboot by modifying the Windows Registry.
- **Process Administration**: Allows starting and stopping programs and services on the target machine.
- **Directory Traversal**: Enables navigation through the target's file system directories.
- **Keylogger (Optional)**: Implements a keylogger to record keystrokes for monitoring user activity.

## Prerequisites

- **Compiler**: 
  - Server: GCC
  - Backdoor: MinGW-w64 (for cross-compiling to Windows)
- **Operating System**: 
  - Target: Windows
  - Development: Any system with GCC and MinGW-w64 installed
- **Libraries**: 
  - `wsock32` and `wininet` for networking functionality (Windows-specific)

## Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/CyberForgeEx/BlackHatOps.git
   cd BlackHatOps/Main Project
   ```

2. **Install Dependencies**:
   Ensure GCC and MinGW-w64 are installed on your development system:
   - On Ubuntu/Debian:
     ```bash
     sudo apt update
     sudo apt install gcc mingw-w64
     ```

## Compilation

### Server
Compile the server program using GCC:
```bash
gcc server.c -o server
```

### Backdoor
Compile the backdoor program using MinGW-w64 for Windows compatibility:
```bash
x86_64-w64-mingw32-gcc -w backdoor.c -o backdoor.exe -lwsock32 -lwininet
```

## Usage

1. **Run the Server**:
   Start the server on your machine to listen for incoming connections:
   ```bash
   ./server
   ```

2. **Deploy the Backdoor**:
   Transfer the compiled `backdoor.exe` to the target Windows machine and execute it. The backdoor will:
   - Establish a connection to the server.
   - Create a stealth shell for remote command execution.
   - Modify the Windows Registry for persistence.
   - Allow process administration and directory traversal.
   - (Optional) Activate the keylogger to record keystrokes.

3. **Interact with the Target**:
   Use the server interface to send commands to the backdoor, such as:
   - Navigating directories.
   - Starting/stopping processes or services.
   - Retrieving keylogger data (if enabled).


## Security Considerations

- **Ethical Use**: Only deploy this tool on systems you have explicit permission to test.
- **Cleanup**: After testing, remove the backdoor from the target system and clean up Registry entries.


