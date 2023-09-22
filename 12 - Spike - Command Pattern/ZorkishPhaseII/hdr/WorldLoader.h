#include <fstream>
#include "Location.h"

/*	This class will take a save file name and from this, extract the relevant
*	data and create a vector of connected Location pointers to be used by the 
*	gameplay state.														   */


/*	I use references when passing strings longer than 15 char as these aren't 
*	handled by C++ small string optimizations								*/

#pragma once
class WorldLoader {
private:
	std::string _file_name;
	std::ifstream _reader;
	
	//	Can replace with a factory if ever expanded
	std::unordered_map<std::string, Item*> _item_pool;	
	std::vector<std::vector<std::string>> _prefmt_world_data;
	std::vector<Location*> _world_data;
	
	std::vector<std::string> readFile();
	void instanceItemPool();
	void processSaveData();
	void instanceWorldData();

	bool isComment(const std::string& line);
	std::vector<std::string> splitSaveLine(std::string& line, const char delimiter);
	Location* getLocationByName(const std::string location_name);
	void wireLocationExits();

public:
	WorldLoader(std::string file_name = "");
	~WorldLoader();

	std::vector<Location*> getWorldData();
	std::vector<Location*> loadWorldData();
};

