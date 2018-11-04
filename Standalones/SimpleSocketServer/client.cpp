#include "client.h"

void SimpleSocketClient::createSocket()
{
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        //return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
      
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, str_address.c_str(), &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        //return -1;
    }
}

void SimpleSocketClient::sendRequestToServer()
{
    this->createSocket();

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        //return -1;
    }
    send(sock, standard_request, strlen(standard_request), 0 );
    valread = read(sock, response_buffer, 1024);
    std::cout << response_buffer << std::endl;
}

void SimpleSocketClient::sendRequestToServer(char* req, int size)
{
    //printf("SimpleSocketClient::sendRequestToServer(char* req, int size)");

    this->createSocket();

    char* request_buffer;

    request_buffer = new char[size];
    strcpy(request_buffer, req);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        //return -1;
    }
    send(sock , request_buffer , strlen(request_buffer) , 0 );
    valread = read(sock , response_buffer, 1024);
    std::cout << response_buffer << std::endl;
    delete[] request_buffer;
}

void SimpleSocketClient::sendRequestToServer(std::string& req)
{
    this->createSocket();

    const char* request_buffer;
    request_buffer = req.c_str();

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        //return -1;
    }
    send(sock, request_buffer, strlen(request_buffer), 0);
    valread = read(sock, response_buffer, 1024);
    std::cout << response_buffer << std::endl;
}