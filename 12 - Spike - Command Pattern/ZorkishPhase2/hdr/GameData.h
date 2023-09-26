#pragma once
#include <queue>
#include <vector>
#include "Location.h"
#include "Player.h"


struct GameData {
	//std::queue<Command*> commands;
	std::vector<Location*> locations;
	Location* current_location;
	Player* player;

	~GameData();
	//void resetCommands();
	void resetLocations();
};

