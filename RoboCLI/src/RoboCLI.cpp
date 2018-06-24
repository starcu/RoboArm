#include <RoboCLI.h>

void RoboCLI::build_json_tree(std::string key, std::string value)
{
	json_response[key] = value;
}

void RoboCLI::build_json_tree(std::string key, int value)
{
	json_response[key] = value;
}

void RoboCLI::build_json_tree(int key, std::string value)
{
	json_response[key] = value;
}

void RoboCLI::build_json_tree(int key, int value)
{
	json_response[key] = value;
}

void RoboCLI::build_json_tree(std::string key, double value)
{
	json_response[key] = value;
}

void RoboCLI::build_json_tree(double key, std::string value)
{
	json_response[key] = value;
}

void RoboCLI::build_json_tree(double key, double value)
{
	json_response[key] = value;
}

void RoboCLI::erase_from_tree(std::string key)
{
	json_response.erase(key);
}

void RoboCLI::erase_from_tree(int key)
{
	json_response.erase(key);
}

void RoboCLI::erase_from_tree(double key)
{
	json_response.erase(key);
}

void RoboCLI::clear_tree()
{
	json_response.clear();
}