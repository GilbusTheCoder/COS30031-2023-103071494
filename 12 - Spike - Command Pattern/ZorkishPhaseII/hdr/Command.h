#include "GameData.h"
#pragma once

class Command {
public:
	virtual void execute(GameData* game_data, std::vector<std::string> args) = 0;
};

class MoveCommand : public Command {
public:
	void execute(GameData* game_data, std::vector<std::string> args) override;
};

