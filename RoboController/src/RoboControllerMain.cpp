#include <iostream>
#include <RoboController.h>

int main(int argc, char const *argv[])
{
	SimpleSocketServer server(8080, "127.0.0.1");
	server.createSocket();

	//std::thread t(&SimpleSocketServer::listenOnSocket, &server);

	std::cout << "Hello from RoboController!!!" << std::endl;
	std::cout << "Read from gyro x = " << 2 << std::endl;
	std::cout << "Read from gyro y = " << 3 << std::endl;
	std::cout << "Read from gyro z = " << 4 << std::endl;

	std::cout << "server start listening on socket" << std::endl;
	//t.join();
	//std::cout << "server start listening on socket" << std::endl;
	server.listenOnSocket();

	return 0;
}