# Basic Socket Program

This directory contains a basic socket program implemented in C, demonstrating client-server communication using TCP sockets. The program is part of the **BlackHatOps** repository, designed for educational and research purposes in offensive security. The **server** is compatible with **Linux**, and the **client** is compatible with **Windows**. This README provides an overview of the code, explains the processes involved, and includes compilation and usage instructions.

## Overview

The Basic Socket Program consists of two C programs:
- **Server (Linux)**: Runs on Linux, listens for incoming connections, and receives messages from a client.
- **Client (Windows)**: Runs on Windows, connects to the server, and sends a message.

These programs demonstrate fundamental socket programming concepts, such as creating a socket, binding it to an address, listening for connections, and exchanging data over a TCP connection.

## Files

- `server.c`: Implements the server-side logic for Linux, accepting client connections and receiving messages.
- `client.c`: Implements the client-side logic for Windows, connecting to the server and sending a message.

## Process Explanation

### Server (`server.c`, Linux)

1. **Socket Creation**:
   - A TCP socket is created using `socket()` with the `AF_INET` address family (IPv4) and `SOCK_STREAM` type (TCP).
   - This socket serves as the endpoint for communication.

2. **Binding the Socket**:
   - The server binds the socket to a specific IP address (e.g., `127.0.0.1`) and port (e.g., `5555`) using `bind()`.
   - The `sockaddr_in` structure specifies the address family, IP, and port.

3. **Listening for Connections**:
   - The `listen()` function configures the socket to accept incoming connections with a specified backlog.
   - The server waits for clients to connect.

4. **Accepting Connections**:
   - The `accept()` function blocks until a client connects, returning a new socket for communication.
   - This example handles one client for simplicity.

5. **Receiving Data**:
   - The server uses `recv()` to receive messages from the client.
   - The received message is printed to the console, and the connection is closed.

6. **Cleanup**:
   - The server closes the client and server sockets using `close()`.

### Client (`client.c`, Windows)

1. **Socket Creation**:
   - A TCP socket is created using `socket()` with `AF_INET` and `SOCK_STREAM`.
   - Winsock is initialized with `WSAStartup()` to enable socket functionality.

2. **Connecting to the Server**:
   - The client specifies the server’s IP address (e.g., `127.0.0.1`) and port (e.g., `5555`) in a `sockaddr_in` structure.
   - The `connect()` function establishes a connection to the server.

3. **Sending Data**:
   - The client sends a predefined message (e.g., "Hello from client") using `send()`.

4. **Cleanup**:
   - The client closes the socket using `closesocket()`.
   - Winsock is cleaned up with `WSACleanup()`.

### Key Socket Concepts

- **TCP Sockets**: Provide reliable, connection-oriented communication.
- **IPv4 Addressing**: Uses `127.0.0.1` (localhost) for local testing.
- **Port Numbers**: The server listens on port `5555`, which the client must match.
- **Platform Differences**: The server uses Linux socket APIs (`sys/socket.h`), while the client uses Winsock (`winsock2.h`).

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/CyberForgeEx/BlackHatOps.git
   ```
2. Navigate to the Basic Socket Program directory:
   ```bash
   cd BlackHatOps/Basic\ Concepts/Basic\ Socket\ Program
   ```

## Compilation

### Server (Linux)
1. Open a terminal on a Linux system.
2. Compile the server:
   ```bash
   gcc -o server server.c
   ```

### Client (Windows)
1. Open a command prompt (e.g., MSYS2 MinGW 64-bit, Git Bash, or PowerShell with MinGW in PATH).
2. Compile the client:
   ```bash
   gcc -o client client.c -lws2_32
   ```

## Usage

1. **Run the Server (Linux)**:
   - In a Linux terminal:
     ```bash
     ./server
     ```
   - The server starts, binds to `127.0.0.1:5555`, and waits for a client connection.

2. **Run the Client (Windows)**:
   - In a Windows terminal:
     ```bash
     ./client.exe
     ```
   - The client connects to the server at `127.0.0.1:5555` and sends a message.

3. **Output**:
   - The server (Linux) prints the message received (e.g., "Message received: Hello from client").
   - The client (Windows) prints "Message sent: Hello from client".
   - Both programs exit after the data transmission.
