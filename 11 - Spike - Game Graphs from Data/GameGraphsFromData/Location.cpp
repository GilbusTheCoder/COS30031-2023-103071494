#include "Location.h"
#include <algorithm>

Location::Location(std::string name,
	std::string description,
	std::unordered_map<std::string, Location*> exits) {
	_name = name;
	_description = description;
	_exits = exits;
}

std::string Location::getName() { return _name; }
std::string Location::getDescription() { return _description; }
Location* Location::getExit(std::string direction) {
	return _exits[direction];
}

std::unordered_map<std::string, Location*> Location::getExits() { return _exits; }

void Location::setName(std::string name) { _name = name; }
void Location::setDescription(std::string description) {
	std::replace(description.begin(), description.end(), '_', ' ');
	_description = description; 
}

void Location::addExit(std::string direction, Location* exit) {
	_exits.insert({ direction, exit });
}

void Location::setAll(std::string name, std::string description,
	std::unordered_map<std::string, Location*> exits) {
	_name = name;
	_description = description;
	_exits = exits;
}

//	FYI if you're running anything earlier than C++ 17 this function will break.
void Location::showExits() {
	std::cout << "Exits: " << std::endl;

	for (auto& [direction, exit] : _exits) {
		std::cout << ">> Location: " << exit->getName()
			<< " -- Direction: " << direction << std::endl;
	}
}

void Location::showDetails() {
	std::cout << "Room: " << _name << std::endl
		<< "Description: " << _description << std::endl;
	showExits(); std::cout << std::endl;
}