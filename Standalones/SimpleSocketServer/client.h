// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <arpa/inet.h>
#include <syscall.h>
#include <unistd.h>
#include <iostream>
#include <memory>
#include <exception>

class SimpleSocketClient
{
private:
    std::string str_address;
    struct sockaddr_in serv_addr;
    unsigned int port;
    int sock = 0, valread;

    const char* standard_request = "Hello from client!";
    int max_buffersize = 1024;
    char* response_buffer = new char[max_buffersize];

    void createSocket();

public:
    SimpleSocketClient(int _port, std::string address): port(_port), 
                                                        str_address(address) {}

    SimpleSocketClient(int _port, std::string address, int buffSize): port(_port), 
                                                                      str_address(address),
                                                                      max_buffersize(buffSize) {}
    void sendRequestToServer();
    void sendRequestToServer(char* req, int size);
    void sendRequestToServer(std::string& req);
    ~SimpleSocketClient() { delete response_buffer; }
};