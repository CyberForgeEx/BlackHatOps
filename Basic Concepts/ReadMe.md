# Basic Concepts

This directory, part of the **BlackHatOps** repository, contains a collection of C programs demonstrating fundamental offensive security techniques for **educational and research purposes**. The programs cover socket programming, reverse shells, shellcode execution, and remote process injection, targeting **Windows** and **Linux** platforms as specified. This README provides an overview of the programs, their purposes, and general setup instructions.

## Overview

The **Basic Concepts** directory includes four programs designed to help security researchers and enthusiasts understand key offensive security techniques in controlled, legal environments. Each program focuses on a specific concept, with platform-specific implementations:

1. **Basic Socket Program**: Demonstrates client-server communication using TCP sockets.
   - `linux-server.c` (Linux): A server that listens for connections and receives messages.
   - `windows-client.c` (Windows): A client that connects to the server and sends a message.
2. **Reverse Shell** (`reverse_shell.c`, Windows): Establishes a reverse shell to an attacker’s machine, redirecting a command shell (`cmd.exe`) via TCP.
3. **Shellcode Execution Program** (`shellcode.c`, Windows): Executes shellcode in memory, demonstrating dynamic code execution.
4. **Remote Process Injection - Shellcode** (`rpi.c`, Windows): Injects shellcode into a remote process and executes it.

**Note**: Some programs, particularly those involving shellcode or reverse shells, may be flagged or blocked by **Windows Defender** or other antivirus software due to their nature. Always test in a controlled, isolated environment (e.g., a virtual machine with antivirus disabled).

## Purpose

These programs are intended for learning and experimentation in offensive security, focusing on:
- **Socket Programming**: Understanding network communication using TCP sockets.
- **Reverse Shells**: Exploring how shells can connect back to an attacker’s machine.
- **Shellcode Execution**: Studying in-memory code execution techniques.
- **Process Injection**: Learning how to inject and execute code in another process’s address space.

Programs must be used only on systems you own or have explicit permission to test, as unauthorized use is **illegal and unethical**.

## Directory Structure

- **Basic Socket Program**:
  - `server.c`: Linux server for TCP communication.
  - `client.c`: Windows client for TCP communication.
- **Reverse Shell**:
  - `reverse_shell.c`: Windows reverse shell client.
- **ShellCode Execution Program**:
  - `shellcode.c`: Windows program for executing shellcode in memory.
- **Remote Process Injection - Shellcode**:
  - `rpi.c`: Windows program for injecting shellcode into a remote process.

## Prerequisites

### Windows (Client for Basic Socket Program, Reverse Shell, Shellcode Execution, Remote Process Injection)
- **MinGW-w64** or **MSYS2** with `gcc`:
  - Install MinGW-w64 from [https://www.mingw-w64.org/](https://www.mingw-w64.org/) or MSYS2 from [https://www.msys2.org/](https://www.msys2.org/).
- **Git**: [https://git-scm.com/downloads](https://git-scm.com/downloads).
- Windows API and Winsock libraries (included with MinGW).

### Linux (Server for Basic Socket Program)
- **GCC**: Install via package manager.
  - Ubuntu/Debian: `sudo apt install build-essential`.
- **Git**:
  - Ubuntu/Debian: `sudo apt install git`.

### Attacker Machine (for Reverse Shell)
- **Netcat**: Used to listen for reverse shell connections.
  - Linux: `sudo apt install netcat` (Ubuntu/Debian).
  - Windows: Download from [https://nmap.org/ncat/](https://nmap.org/ncat/).

## Antivirus Warning

The **Reverse Shell**, **Shellcode Execution**, and **Remote Process Injection** programs involve techniques commonly associated with malware, so **Windows Defender** or other antivirus software may flag or block them. To test these programs:
- Use a virtual machine with antivirus disabled.
- Add an exception in Windows Defender for the compiled binaries (not recommended for production systems).
- Run in a sandboxed or isolated environment to avoid interference.

## Troubleshooting
- **General**:
  - Verify network connectivity for socket and reverse shell programs.
  - Ensure correct IP/port configurations and no firewall restrictions.
  - Check shellcode compatibility with the target system’s architecture (e.g., 32-bit vs. 64-bit).

## Disclaimer

These programs are for **educational and research purposes only**. They must be used only on systems you own or have explicit permission to test. Unauthorized use, including executing code or establishing connections without consent, is **illegal and unethical**. The developers are not responsible for misuse or damages. Always comply with local laws and regulations.
