#ifndef REDIS_COMMAND_HANDLER_H
#define REDIS_COMMAND_HANDLER_H

#include <string>

class RedisCommandHandler
{
public:
    // Constructor
    RedisCommandHandler();

    // process a comman from the client and return RESP-Formatted response.
    std::string processCommand(const std::string &commandLine);
};

#endif