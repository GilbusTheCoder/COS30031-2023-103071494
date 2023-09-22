#include <iostream>
#include <fstream>
#include <vector>
#include "Location.h"

#pragma once
class WorldLoader {
private:
	std::string _file_name;
	std::ifstream _reader;
	std::vector<std::vector<std::string>> _prelim_world_data;
	std::vector<std::vector<Location*>> _world_data;

	bool isComment(const std::string line);
	std::vector<std::string> splitSaveLine(const std::string line, const char delimiter);
	std::vector<std::string> pullSaveData();
	void processSaveData();

public:
	WorldLoader(std::string file_name = "");
	~WorldLoader();

	std::vector<std::vector<Location*>> getWorldData();
	void formatSaveData();
};

