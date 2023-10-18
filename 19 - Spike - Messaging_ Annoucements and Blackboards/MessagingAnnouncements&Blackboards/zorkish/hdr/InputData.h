#include "Command.h"
#pragma once
struct InputData {
	CommandType c_type = CommandType::INVALID;
	std::vector<std::string> _args = {};
};