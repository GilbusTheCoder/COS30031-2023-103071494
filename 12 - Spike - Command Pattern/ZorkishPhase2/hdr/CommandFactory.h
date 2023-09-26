#pragma once
#include "Command.h"

class CommandFactory {
public:
	std::queue<Command*> createCommands(std::string c_type, 
		std::vector<std::string> c_args);
};