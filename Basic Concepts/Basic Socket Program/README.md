# Basic Socket Program

This directory contains a basic socket program implemented in C, demonstrating client-server communication using TCP sockets. The program is part of the **BlackHatOps** repository, designed for educational and research purposes in offensive security. This README provides an overview of the code, explains the processes involved, and includes compilation and usage instructions for both **Windows** and **Linux** platforms.

## Overview

The Basic Socket Program consists of two C programs:
- **Server**: Listens for incoming connections and receives messages from a client.
- **Client**: Connects to the server and sends a message.

These programs demonstrate fundamental socket programming concepts, such as creating a socket, binding it to an address, listening for connections, and exchanging data over a TCP connection.

## Files

- `server.c`: Implements the server-side logic for accepting client connections and receiving messages.
- `client.c`: Implements the client-side logic for connecting to the server and sending a message.

## Process Explanation

### Server (`server.c`)

1. **Socket Creation**:
   - A TCP socket is created using the `socket()` function with the `AF_INET` address family (IPv4) and `SOCK_STREAM` type (TCP).
   - This socket serves as the endpoint for communication.

2. **Binding the Socket**:
   - The server binds the socket to a specific IP address (e.g., `127.0.0.1`) and port (e.g., `5555`) using the `bind()` function.
   - The `sockaddr_in` structure specifies the address family, IP, and port.

3. **Listening for Connections**:
   - The `listen()` function configures the socket to accept incoming connections, with a specified backlog for pending connections.
   - The server waits for clients to connect.

4. **Accepting Connections**:
   - The `accept()` function blocks until a client connects, returning a new socket for communication with the client.
   - The server can handle multiple clients by iterating or threading (this example handles one client for simplicity).

5. **Receiving Data**:
   - The server uses `recv()` to receive messages from the client.
   - The received message is printed to the console, and the connection is closed.

6. **Cleanup**:
   - The server closes the client and server sockets using `close()` (Linux) or `closesocket()` (Windows).
   - On Windows, the Winsock library is cleaned up with `WSACleanup()`.

### Client (`client.c`)

1. **Socket Creation**:
   - A TCP socket is created similarly to the server, using `socket()` with `AF_INET` and `SOCK_STREAM`.

2. **Connecting to the Server**:
   - The client specifies the server’s IP address and port in a `sockaddr_in` structure.
   - The `connect()` function establishes a connection to the server.

3. **Sending Data**:
   - The client sends a predefined message (e.g., "Hello from client") to the server using the `send()` function.

4. **Cleanup**:
   - The client closes the socket using `close()` (Linux) or `closesocket()` (Windows).
   - On Windows, `WSACleanup()` is called to clean up Winsock.

### Key Socket Concepts

- **TCP Sockets**: Provide reliable, connection-oriented communication.
- **IPv4 Addressing**: Uses `127.0.0.1` (localhost) for local testing.
- **Port Numbers**: The server listens on a specific port (e.g., `5555`), which the client must match.
- **Winsock (Windows)**: Requires initialization with `WSAStartup()` and linking with `-lws2_32`.

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

### Windows
2. Compile the server:
   ```bash
   gcc -o server server.c -lws2_32
   ```
3. Compile the client:
   ```bash
   gcc -o client client.c -lws2_32
   ```

### Linux
2. Compile the server:
   ```bash
   gcc -o server server.c
   ```
3. Compile the client:
   ```bash
   gcc -o client client.c
   ```

## Usage

1. **Run the Server**:
   - Windows: `./server.exe`
   - Linux: `./server`
   - The server starts, binds to `127.0.0.1:5555`, and waits for a client connection.

2. **Run the Client** (in a separate terminal):
   - Windows: `./client.exe`
   - Linux: `./client`
   - The client connects to the server at `127.0.0.1:5555` and sends a message.

3. **Output**:
   - The server prints the message received from the client (e.g., "Message received: Hello from client").
   - Both programs exit after the data transmission.
