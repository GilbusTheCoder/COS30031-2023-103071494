#pragma once
#include "GameData.h"
class Command {
public:
	virtual void execute(GameData* game_data, std::vector<std::string> args) = 0;
};

// The direction is the first and only argument contained in args
class MoveCommand : public Command {
public:
	void execute(GameData* game_data, std::vector<std::string> args) override;
};

