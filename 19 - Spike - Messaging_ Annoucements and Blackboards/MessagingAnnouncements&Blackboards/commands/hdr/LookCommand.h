#include "Command.h"
#include "../../zorkish/hdr/InputData.h"

#pragma once

enum class LookTriggerType {
	LOOK_ALL,
	LOOK_SPECIFIC,
	LOOK_CONTAINER,
	LOOK_INVALID,
};

class LookCommand : virtual public Command {
private:
	GameData* _game_data;
	InputData* _input_data;

public:
	void setData(GameData* game_data, InputData* input_data);
	void triggerEvent() override;

private:
	LookTriggerType determineTriggerType();

	void lookAtAll();
	void lookAtSpecific();
	void lookAtContainer();

	std::string extractUEID(std::string ucid);
};


