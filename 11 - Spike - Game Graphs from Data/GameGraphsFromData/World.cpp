#include <iostream>
#include <fstream>
#include <vector>

#include "World.h"
#include "WorldLoader.h"
#include "Location.h"

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
}

void World::addLocation(Location* new_location)
	{ _locations.push_back(new_location); }

void World::changeCurrentLocation(std::string location_name) {
	for (auto it : _locations) {
		if (it->getName() == location_name) { _current_location = it; }
	}
}

void World::showCurrentLocation() { _current_location->showDetails(); }
void World::showLocations() { for (auto it : _locations) { it->showDetails(); } }

/*	Here is a funny function. This will load everything except exit data into a location.
*	The exit data will be done on a second pass as the structure requires the location to
*	own a name in to search it in the vector.	*/
void World::loadLocationData() {
	//Delimiters
	char first_pass_delim = ';';
	char second_pass_delimiter = ':';

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
			_locations[room_idx]->addExit(getLocationByName(formatted_room_data[room_idx][exit_idx]));
		}
	}
}