#ifndef REDIS_SERVER_H
#define REDIS_SERVER_H

#include <atomic>
#include <string>

class RedisServer
{
public:
    RedisServer(int port);
    void start();
    void stop();
};

private:
int port;
int server_socket;
std::atomic<bool> running;
/*
 ensures that changes to this variable are visible
 across multiple threads without data races, which
 is important for safely starting and stopping the
 server in a multithreaded environment.
*/
}
;

#endif

/*
This prevents the contents of the header file
 from being included multiple times in a single
compilation, which can cause errors.
If the file is included again,
REDIS_SERVER_H will already be defined, so
the code between #ifndef and #endif will be
skipped.
*/