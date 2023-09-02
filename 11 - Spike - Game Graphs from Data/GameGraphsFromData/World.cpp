#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "World.h"

std::vector<Location*> World::constructLocations() {
	std::vector<Location*> locations;

	//Allocate Memory for rooms
	Location* lounge_room = new Location();
	Location* courtyard = new Location();
	Location* bedroom = new Location();
	Location* backyard = new Location();

	//Push those pointers to _locations
	locations.push_back(lounge_room);
	locations.push_back(courtyard);
	locations.push_back(bedroom);
	locations.push_back(backyard);

	return locations;
}

Location* World::getLocationByName(std::string location_name) {
	for (auto location : _locations) {
		if (location->getName() == location_name) { return location; }
	}
}

World::World() {
	_locations = constructLocations();

	if (_current_location != nullptr) {
		_locations.push_back(_current_location);
	}
	else { _current_location = _locations[0]; }
}

World::~World() {
	delete _reader;
}

bool World::checkIsRunning() { return _is_running; }

void World::addLocation(Location* new_location)
	{ _locations.push_back(new_location); }

void World::showCurrentLocation() { _current_location->showDetails(); }

void World::showLocations() { 
	for (auto location : _locations) {
		location->showDetails(); 
	} 
}

/*	Here is a funny function. This will load everything except exit data into a location.
*	The exit data will be done on a second pass as the structure requires the location to
*	own a name in to search it in the vector.	*/
void World::loadLocationData() {
	//Delimiters
	char first_pass_delim = ';';
	char second_pass_delimiter = ':';
	char third_pass_delimiter = ',';

	std::vector<std::string> unformatted_room_data = _reader->getLinesByDelimiter(first_pass_delim);
	std::vector<std::vector<std::string>> formatted_room_data;

	for (auto room_data_set : unformatted_room_data) {
		room_data_set += second_pass_delimiter; // Add the delimiter to the end of the line
		std::vector<std::string> formatted_line = _reader->splitLine(room_data_set, second_pass_delimiter);
		formatted_room_data.push_back(formatted_line);
	}

	for (int room_idx = 0; room_idx < formatted_room_data.size(); room_idx++) {
		_locations[room_idx]->setName(formatted_room_data[room_idx][0]);
		_locations[room_idx]->setDescription(formatted_room_data[room_idx][1]);
	}

	// It's assumed that the locations in the load file are in the same order as in the 
	// _locations vector.
	for (int room_idx = 0; room_idx < formatted_room_data.size(); room_idx++) {
		for (int exit_idx = 2; exit_idx < formatted_room_data[room_idx].size(); exit_idx++) {
			std::vector<std::string> split_direction_location =
				_reader->splitLine(formatted_room_data[room_idx][exit_idx]+=third_pass_delimiter, third_pass_delimiter);
			_locations[room_idx]->addExit(split_direction_location[0], getLocationByName(split_direction_location[1]));
		}
	}
}

/*	Needs to be able to take input from the player, translate that into a direction and
*	change the players current location based off this input. 
* 
*	
*/
std::string World::processDirectionInput(std::string dir) {
	std::string direction = dir;
	std::transform(direction.begin(), direction.end(), direction.begin(),
		[](unsigned char c) { return std::tolower(c); });	// To lower

	if (direction == "north" || direction == "n" ||
		direction == "forward" || direction == "up")
	{
		return "north";
	}

	else if (direction == "east" || direction == "e" || direction == "right")
	{
		return "east";
	}
	
	else if (direction == "south" || direction == "s" ||
		direction == "back" || direction == "backwards" || direction == "down")
	{
		return "south";
	}
	
	else if (direction == "west" || direction == "w" || direction == "left") {
		return "west";
	}

	else { return "error"; }
}

bool World::checkDirectionsValid(std::string dir) {
	if (std::find(_valid_directions.begin(), _valid_directions.end(), dir) != _valid_directions.end())
	{
		std::string direction = processDirectionInput(dir);
		std::unordered_map<std::string, Location*> current_exits = _current_location->getExits();
		std::unordered_map<std::string, Location*>::const_iterator exit = current_exits.find(direction);

		return exit != current_exits.end();
	}
	
	return false;
}

void World::update() {
	std::string action;
	std::string direction;

	std::cin >> action;
	std::cin >> direction;
	std::cout << std::endl;

	if (action == "quit") {	_is_running = false;	}
	else if (action == "go") { 
		if (checkDirectionsValid(direction)) {
			_current_location = _current_location->getExits()[processDirectionInput(direction)];
		}
	}
}

void World::render() {
	std::cout << std::endl;
	std::cout << "--------------------------------------------------------------" << std::endl;
	std::cout << "Room: " << _current_location->getName() << std::endl;
	std::cout << _current_location->getDescription() << std::endl;
	std::cout << std::endl;
	std::cout << "Where do you want to go?" << std::endl;
	std::cout << ">> ";
}

