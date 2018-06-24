#include <iostream>
#include <RoboCLI.h>

RoboCLI rCLI;

int main(int argc, char const *argv[])
{
	rCLI.build_json_tree("ID", 1);
	rCLI.build_json_tree("x", 1.23);
	rCLI.build_json_tree("y", 2.34);
	rCLI.build_json_tree("z", 3.45);

	rCLI.print_json_response_to_cout();

	std::cout << "socket client request" << std::endl;
	SimpleSocketClient client(8080, "127.0.0.1");
    client.sendRequestToServer();

	return 0;
}