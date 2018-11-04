#include "client.h"

int main(int argc, char** argv)
{
    SimpleSocketClient client(8080, "127.0.0.1");
    
    std::string msg("");
    try
    {
	msg = std::string(argv[1]);
    } 
    catch(...)
    {
        msg = "Hello from client!!!";
	std::cout << "conversion failed, sending default mesage." << std::endl;
    }
    //client.sendRequestToServer();
    //std::string rs = "String request";
    client.sendRequestToServer(msg);
    //char* r = "char buffer request";
    //client.sendRequestToServer(r, 1024);

    return 0;
}

