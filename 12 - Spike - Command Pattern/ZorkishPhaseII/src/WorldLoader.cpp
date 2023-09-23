#include <string>
#include <algorithm>
#include "../hdr/WorldLoader.h"

/******************************************************************************
*							    De/Constructors
******************************************************************************/
WorldLoader::WorldLoader(std::string file_name)
	:_file_name(file_name) {

	if (_file_name == "") { std::cout << "Err: No filename supplied." << std::endl; }
	else {
		_reader.open(_file_name);

		if (!_reader.is_open()) {
			std::cout << "Err: Bad filename supplied" << std::endl;
		}
	}
}

// Must be using C++ 17 or newer for this map search to work.
WorldLoader::~WorldLoader() { 
	if (_reader.is_open()) { _reader.close(); } 

	for (auto& location : _world_data) {
		delete location;
		location = nullptr;
	}

	for (auto& [item_name, item] : _item_pool) {
		delete item;;
		item = nullptr;
	}

	_world_data.clear();
	_item_pool.clear();
};


/******************************************************************************
*								  Properties
******************************************************************************/
std::vector<Location*> WorldLoader::getWorldData() { return _world_data; }


/******************************************************************************
*							  Core Functionality
*******************************************************************************
*	Private:																 */

/*	First pass on the text file, will just extract the data line by line removing
*	whitespace. Will return a vector<string>.								   */
std::vector<std::string> WorldLoader::readFile() {
	std::string line;
	std::vector<std::string> lines;

	if (!_reader.is_open() && _file_name != "") { _reader.open(_file_name); }
	if (_reader.is_open()) {
		while (std::getline(_reader, line)) {
			std::vector<std::string> line_hack;
			// Remove Whitespace
			remove(line.begin(), line.end(), ' ');
			line_hack = splitSaveLine(line, ';');

			// Check if comment
			if (!isComment(line_hack[0])) {
				lines.emplace_back(line_hack[0]);
			}
		}
	}

	return lines;
}

/*	Any new world items which are to be read from the game file will be first
*	created here. This method instantiates and appends the items to the
*	_item_pool.																*/
void WorldLoader::instanceItemPool() {
	Item* twigs = new Item("twigs", "cool and twig-like");
	Item* sword_of_testing = new Item("sword of testing", "good for testing stuff");
	Item* pot_of_testing = new Item("pot of testing", "better for testing stuff");
	Item* firebound_scroll = new Item("firebound scroll", "boom boom pew.");

	_item_pool.insert({ twigs->getName(), twigs });
	_item_pool.insert({ sword_of_testing->getName(), sword_of_testing });
	_item_pool.insert({ pot_of_testing->getName(), pot_of_testing });
	_item_pool.insert({ firebound_scroll->getName(), firebound_scroll });
	// Cleanup is handled by the Gameplay State
}


/*	Updates the _prefmt_world_data such that each subvector is formatted:
	<"name" : "desc" : "i0.name, i1.name,..." : "dir0, exit0_name,...">
	<"name" : "desc" : "i0.name, i1.name,..." : "dir0, exit0_name,...">
	... <...>	*/
void WorldLoader::processSaveData() {
	std::vector<std::string> raw_save_data = readFile();

	if (!raw_save_data.empty()) {
		for (auto save_set : raw_save_data) {
			_prefmt_world_data.emplace_back(splitSaveLine(save_set, ':'));
		}
	}
}

/*	For each set of location data in the loaders _prefmt_world_data, create
*	a new location object and assign it a name and a description. This method
*	will not throw an error if the name doesn't return an item, the item will
*	not be added though.
*
*	Note: The exit data will be instantiated in a seperate pass. Additionally,
*	deletion of this data is handled by the gameplay state					*/
void WorldLoader::instanceWorldData() {
	for (auto location : _prefmt_world_data) {
		Location* new_location = new Location();
		new_location->setName(location[0]);
		new_location->setDescription(location[1]);

		std::vector<std::string> item_names = splitSaveLine(location[2], ',');
		for (auto name : item_names) {
			std::replace(name.begin(), name.end(), '_', ' ');
			if (_item_pool[name]) { new_location->addItem(_item_pool[name]); }
		}

		_world_data.emplace_back(new_location);
	}

	// After everythings named we can wire the exits
	wireLocationExits();
}


/******************************************************************************
*								   Utility
*******************************************************************************
*	Private:																 */
bool WorldLoader::isComment(const std::string& line) {
	std::string string_data = line;
	
	if (string_data[0] == '#') { return true; }
	return false;	
}

/*	Splits a string around a delimiting character.Returns the split string as
*	std::vector<std::string>												*/
std::vector<std::string> WorldLoader::splitSaveLine(std::string& line, 
	const char delimiter) {
	int start_idx = 0, end_idx = 0;
	std::string raw_line_data = line+=delimiter;
	std::vector<std::string> formatted_line_data;

	for (int idx = 0; idx <= raw_line_data.size(); idx++) {
		if (char(raw_line_data[idx]) == delimiter) {
			std::string line_datum;
			end_idx = idx;
			
			line_datum.append(raw_line_data, start_idx, end_idx - start_idx);
			formatted_line_data.emplace_back(line_datum);

			start_idx = ++end_idx;
		}
	}

	return formatted_line_data;
}


// Can only be called after the world data has been instanced with a name.
Location* WorldLoader::getLocationByName(std::string location_name) {
	for (auto& location : _world_data) {
		if (location->getName() == location_name) { return location; }
	}
}

void WorldLoader::wireLocationExits() {
	// The _prefmt_world_data is the same size as our _world_data. We use this yes yes.
	// First element will a dir, second an exit name. Last element always exit
	std::vector<std::string> raw_dir_exit_data;

	for (int loc_idx = 0; loc_idx < _world_data.size(); loc_idx++) {
		// <"dir0", "exit0_name", "dir1", "exit1_name", .... , "dirn", exitn_name">
		raw_dir_exit_data = splitSaveLine(_prefmt_world_data[loc_idx][3], ',');
	
		for (int datum_idx = 0; datum_idx < raw_dir_exit_data.size(); 
			datum_idx += 2) {
			_world_data[loc_idx]->addExit(raw_dir_exit_data[datum_idx],
				getLocationByName(raw_dir_exit_data[datum_idx + 1]));
		}
	}	
}

/*****************************************************************************	
*   Public:																	*/	
void WorldLoader::loadWorldData() {
	if (_reader.is_open()) {
		instanceItemPool();
		processSaveData();
		instanceWorldData();
	}
}