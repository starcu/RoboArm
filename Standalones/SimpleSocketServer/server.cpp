#include "server.h"

void SimpleSocketServer::createSocket()
{
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(address_str.c_str());//INADDR_ANY;
    address.sin_port = htons(port);
      
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
}

void SimpleSocketServer::listenOnSocket()
{
    while(1)
    {
        if ((new_socket = accept(server_fd, 
                                (struct sockaddr*)&address, 
                                (socklen_t*)&addrlen))<0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        char request_buffer[max_buffersize];
        memset (request_buffer, 0, max_buffersize);
        valread = read(new_socket, request_buffer, max_buffersize);
        send(new_socket, standard_response, strlen(standard_response), 0);
        std::cout << request_buffer << std::endl;
    }
}


int main()
{
    SimpleSocketServer server(8080, "127.0.0.1");
    server.createSocket();
    server.listenOnSocket();

    return 0;
}
