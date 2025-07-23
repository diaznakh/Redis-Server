#include "../include/RedisServer.h"
#include <iostream>

int main(int argc, char* argv[]) {
    int port = 6379; // Default Redis port

    /*
    If the user provides at least one argument after 
    the program name (argc >= 2), this line 
    converts the first argument (argv[1]) 
    from a string to an integer using 
    std::stoi and assigns it to port.
    This allows the user to specify a custom 
    port when starting the server, 
    e.g., ./main 6380 will set port to 6380.
    If no argument is given, the default port 
    6379 is used
    */
   
    if (argc >= 2)  port = std::stoi(argv[1]);

    RedisServer server(port);

    return 0;
}