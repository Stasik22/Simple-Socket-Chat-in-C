Simple Socket Chat in C

This repository contains a minimal implementation of a chat system using TCP sockets in C. It includes both server and client programs that allow two users to exchange messages over a network.

Features

Simple and easy-to-understand implementation

Uses TCP for reliable communication

Works on Linux and macOS

Single function for sending and receiving messages

Requirements

A C compiler (e.g., gcc)

POSIX-compatible operating system (Linux/macOS)

Compilation

To compile the server and client programs, use the following commands:

gcc server.c -o server
gcc client.c -o client

Usage

Start the server

./server

The server will wait for incoming client connections.

Connect a client

On another terminal or machine, run:

./client <server_ip>

Replace <server_ip> with the actual IP address of the machine running the server.

Start chatting

Once the client is connected, you can exchange messages between the server and the client.

Dependencies

Standard C libraries: sys/socket.h, netinet/in.h, arpa/inet.h, unistd.h, stdio.h, stdlib.h, string.h

License

This project is licensed under the MIT License. Feel free to modify and distribute it.

Contribution

Contributions are welcome! Feel free to submit a pull request or open an issue if you have any improvements or suggestions.

