#include "../hdr/GameData.h"

GameData::~GameData() {
	resetLocations();

	delete player;
	player = nullptr;
}

//void GameData::resetCommands() {
//	while (!commands.empty()) {
//		delete commands.front();
//		commands.front() = nullptr;
//		commands.pop();
//	}
//}

void GameData::resetLocations() {
	for (int idx = 0; idx < locations.size(); idx++) {
		delete locations[idx];
		locations[idx] = nullptr;
	}

	locations.clear();
	locations.shrink_to_fit();
}