#pragma once
#include <queue>
#include <vector>
#include "Location.h"
#include "Player.h"

struct GameData {
	bool quit = false;
	std::vector<Location*> locations;
	Location* current_location;
	Player* player;

	~GameData();
	void resetLocations();
};
