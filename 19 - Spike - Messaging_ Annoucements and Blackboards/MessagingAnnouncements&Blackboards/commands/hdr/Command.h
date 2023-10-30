#include "../../zorkish/hdr/GameData.h"

#pragma once
enum CommandType {
	INVALID,
	MOVE,	// go somewhere
	TAKE,	// transfer item
	LOOK,	// display surrounding renderer info
	SHOW,	// display attached component info
	QUIT,	// change game_data is_running to false
};

class Command {
public:
	virtual void triggerEvent() = 0;
};
