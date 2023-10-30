#include "Command.h"
#pragma once

class QuitCommand : virtual public Command {
private:
	GameData* _game_data = nullptr;

public:
	QuitCommand();

	void setData(GameData* game_data_frame);
	void triggerEvent() override;
};
