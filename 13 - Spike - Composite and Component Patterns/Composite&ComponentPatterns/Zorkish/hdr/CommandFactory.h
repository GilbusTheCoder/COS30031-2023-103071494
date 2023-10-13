#include <queue>
#include "Command.h"

#pragma once
class CommandFactory {
public:
	std::queue<Command*> createCommands(GameData* game_data,
		CommandType c_type, std::vector<std::string> c_args = {});
};

