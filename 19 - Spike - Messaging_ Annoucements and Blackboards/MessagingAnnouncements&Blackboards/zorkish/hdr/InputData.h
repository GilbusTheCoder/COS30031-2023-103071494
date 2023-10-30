#include "../../commands/hdr/Command.h"

#pragma once
struct InputData {
	CommandType c_type = CommandType::INVALID;
	std::vector<std::string> args = {};

	C_Inventory* src = nullptr;
	C_Inventory* dest = nullptr;
	Entity* item = nullptr;
};