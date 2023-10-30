#include "Command.h"
#pragma once

class ShowCommand : virtual public Command {
private:
	GameData* _game_data;
	std::string _modifier;

public:
	void setData(GameData* game_data, std::string arg);
	void triggerEvent() override;

private:
	std::string extractUEID(std::string ucid);
};

