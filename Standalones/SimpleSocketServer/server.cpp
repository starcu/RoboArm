#include "server.h"

void SimpleSocketServer::createSocket()
{
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        throw std::exception("SERVER_FAILED_SOCKET_CREATION");
    }
      
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        throw std::exception("SERVER_FAILED_SOCKET_CREATION");
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(address_str.c_str());//INADDR_ANY;
    address.sin_port = htons(port);
      
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        throw std::exception("SERVER_INIT_BIND_FAILED_EXIT_FAILURE");
    }

    if (listen(server_fd, 3) < 0)
    {
        throw std::exception("SERVER_LISTEN_ERROR_EXIT_FAILURE");
    }
}

void SimpleSocketServer::listenOnSocket(bool block)
{
    do // with block set to false its possible to use this function in external while loop
    {
        if ((new_socket = accept(server_fd, 
                                (struct sockaddr*)&address, 
                                (socklen_t*)&addrlen))<0)
        {
            throw std::exception("SERVER_ACCEPT_INCOME_REQ_ERROR");
        }

        char request_buffer[max_buffersize];
        memset (request_buffer, 0, max_buffersize);
        valread = read(new_socket, request_buffer, max_buffersize);
        send(new_socket, standard_response, strlen(standard_response), 0);
        std::cout << request_buffer << std::endl;
    }
    while(block)
}
