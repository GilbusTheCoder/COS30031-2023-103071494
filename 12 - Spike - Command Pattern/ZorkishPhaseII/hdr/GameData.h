#pragma once

#include <vector>
#include "Location.h"
#include "Player.h"


struct GameData {
	std::vector<Location*> locations;
	Location* current_location = nullptr;
	Player* player = nullptr;
};

