#include <fstream>

#include "EntityFactory.h"
#include "GameData.h"

#pragma once
/*	This little fella will take a string reference to a save file and from there
*	instantiate the one and only GameData struct for use within the gameplay
*	state.
*
*	The World loader owns the entity factory and will call it's methods to
*	construct the worlds entities and fill out the GameData instance.		 */
class WorldLoader {
private:
	std::string _file_name;
	std::ifstream _reader;
	GameData* _game_data = nullptr;
	EntityFactory* _entity_factory = nullptr;

	std::vector<std::string> readFile();
	std::vector<std::string> splitSaveLine(std::string& line, const char delimiter);
	bool isComment(const std::string& line);

public:
	WorldLoader(const std::string& file_name = "");
	~WorldLoader();

	void setSaveFile(const std::string& file_name);
	GameData* loadGameData();
};

