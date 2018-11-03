
// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <arpa/inet.h>
#include <iostream>

class SimpleSocketServer
{
    private:
    std::string address_str;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    unsigned int port = 8080;
    unsigned int server_fd, new_socket, valread;
    int opt = 1;

    unsigned int max_buffersize = 1024;
    char* standard_response = "Hello from C++ server!";
    char* response;

    void prepareResponse();

    public:
    SimpleSocketServer(int _port, std::string address): port(_port), address_str(address) {}
    void createSocket();
    void listenOnSocket();
    ~SimpleSocketServer() { }
};