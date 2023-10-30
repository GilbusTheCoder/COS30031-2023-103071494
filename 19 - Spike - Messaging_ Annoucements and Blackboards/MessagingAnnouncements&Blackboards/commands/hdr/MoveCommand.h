#include "Command.h"

#pragma once
class MoveCommand : virtual public Command {
private:
	GameData* _game_data = nullptr;
	std::string _exit_UEID;

public:
	MoveCommand();

	void setData(GameData* game_data_frame, std::string exit_UEID);
	void triggerEvent() override;
};
