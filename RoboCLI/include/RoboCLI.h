#ifndef ROBOCLI_H
#define ROBOCLI_H

#include <iostream>
#include <json.h>
#include "client.h"

using json = nlohmann::json;

enum command
{
	command_1,
	command_2,
	command_3
};

class RoboCLI
{
private:
	json json_response;
public:
	void build_json_tree(std::string key, std::string value);
	void build_json_tree(std::string key, int value);
	void build_json_tree(int key, std::string value);
	void build_json_tree(int key, int value);
	void build_json_tree(std::string key, double value);
	void build_json_tree(double key, std::string value);
	void build_json_tree(double key, double value);
	void erase_from_tree(std::string key);
	void erase_from_tree(int key);
	void erase_from_tree(double key);
	void clear_tree();
	std::string return_json_response_as_str() const { return json_response.dump(); }
	void print_json_response_to_cout() const { std::cout << json_response.dump() << std::endl; }
};

#endif