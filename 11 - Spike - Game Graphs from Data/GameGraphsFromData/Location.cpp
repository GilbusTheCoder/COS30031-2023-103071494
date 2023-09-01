#include "Location.h"

Location::Location(std::string name = " ",
	std::string description = " ",
	std::vector<Location*> exits = {}) {
	_name = name;
	_description = description;
	_exits = exits;
}

std::string Location::getName() { return _name; }
void Location::setName(std::string name) { _name = name; }
void Location::setDescription(std::string description) { _description = description; }
void Location::addExit(Location* exit) { _exits.push_back(exit); }
void Location::setAll(std::string name, std::string description, std::vector<Location*> exits) {
	_name = name;
	_description = description;
	_exits = exits;
}

void Location::showExits() {
	std::string exit_name;
	std::cout << "Exits: " << std::endl;

	for (auto it : _exits) {
		exit_name = it->getName();
		std::cout << ">> " << exit_name << std::endl;
	}
}

void Location::showDetails() {
	std::cout << "Room: " << _name << std::endl
		<< "Description: " << _description << std::endl;
	showExits(); std::cout << std::endl;
}