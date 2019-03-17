#ifndef ROBOCLI_H
#define ROBOCLI_H

#include <iostream>
#include <json.h>
#include "client.h"

using json = nlohmann::json;

class RoboCLI
{
private:
	json json_response;

public:
	template<class KEY, class VALUE>
	void build_json_tree(KEY key, VALUE value);
	
	template<class KEY>
	void erase_from_tree(KEY key);
	
	void clear_tree();
	std::string return_json_response_as_str() const { return json_response.dump(); }
	void print_json_response_to_cout() const { std::cout << json_response.dump() << std::endl; }
};

template<class KEY, class VALUE>
void RoboCLI::build_json_tree(KEY key, VALUE value)
{
	json_response[key] = value;
}

template<class KEY>
void RoboCLI::erase_from_tree(KEY key)
{
	json_response.erase(key);
}

class RoboCLIException {};

#endif