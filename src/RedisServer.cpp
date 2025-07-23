#include "../include/RedisServer.h"

#include <iostream>
#include <unistd.h> // For close()
#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in


static RedisServer* globalServer = nullptr;

RedisServer::RedisServer(int port) : port(port), server_socket(-1), running(true{
    globalServer = this;
}

void RedisServer::stop() {
    running = false;
    if (server_socket != -1) {
        close(server_socket);
    }
    std::cout << "Server stopped!" << std::endl;
}

void RedisServer::start() {
    // Create a socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        std::cerr << "Error creating socket!" << std::endl;
        return;
    }

    int opt = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the address and port
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error binding socket!" << std::endl;
        return;
    }

    // Start listening for incoming connections
    if (listen(server_socket, 10) < 0) {
        std::cerr << "Error listening on socket!" << std::endl;
        return;
    }

    std::cout << "Server started on port " << port << std::endl;

    // Main loop to accept connections
    while (running) {
        int client_socket = accept(server_socket, nullptr, nullptr);
        if (client_socket < 0) {
            if (running) { // Only print error if we are still running
                std::cerr << "Error accepting connection!" << std::endl;
            }
            continue;
        }
        // Handle client connection here (e.g., read/write data)
        close(client_socket); // Close client socket after handling
    }

    stop();
}