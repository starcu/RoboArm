#include "server.h"

int main()
{
    SimpleSocketServer server(8080, "127.0.0.1");
    server.createSocket();
    server.listenOnSocket();

    return 0;
}

