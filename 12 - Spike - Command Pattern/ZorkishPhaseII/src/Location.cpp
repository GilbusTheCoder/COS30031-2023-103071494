#include "../hdr/Location.h"

/******************************************************************************
*							    De/Constructors
******************************************************************************/
Location::Location(std::string name, std::string description, std::unordered_map<std::string, Location*> exits)
	: _name(name), _description(description), _exits(exits) {}


/******************************************************************************
*								  Properties
******************************************************************************/
std::string Location::getName() { return _name; }
std::string Location::getDescription() { return _description; }
Location* Location::getExit(std::string direction) { return _exits[direction]; }
std::unordered_map<std::string, Location*> Location::getExits() { return _exits; };

void Location::setName(std::string name) { _name = name; }
void Location::setDescription(std::string description) { _description = description; }
void Location::setExits(std::unordered_map<std::string, Location*> exits) { _exits = exits; }
void Location::setAll(std::string name, std::string description,
	std::unordered_map<std::string, Location*> exits) {
	_name = name;
	_description = description;
	_exits = exits;
}

/******************************************************************************
*								   Utility
******************************************************************************/
void Location::addExit(std::string direction, Location* exit) {
	_exits.insert({ direction, exit });
}

//	FYI if you're running anything earlier than C++ 17 this function will break.
void Location::showExits(){
	std::cout << "Exits:" << std::endl;

	for (auto& [direction, exit] : _exits) {
		std::cout << "Location: " << exit->getName() << std::endl;
		std::cout << "Direction: " << direction << std::endl << std::endl;
	}
}

void Location::about() { 
	std::cout << "Name: " << _name << std::endl;
	std::cout << "Description: " << _description << std::endl;
	
	showExits();
}
