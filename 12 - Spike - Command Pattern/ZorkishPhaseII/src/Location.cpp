#include <algorithm>
#include "../hdr/Location.h"


/******************************************************************************
*							    De/Constructors
******************************************************************************/
Location::Location(std::string name, std::string description, 
	std::vector<Item*> items,
	std::unordered_map<std::string, Location*> exits)
	: _name(name), _description(description), _items(items), _exits(exits) {}

Location::~Location() {
	for (auto& item : _items) { delete item; item = nullptr; }

	for (auto& [dir, location] : _exits) {
		delete location;
		location = nullptr;
	}
	_items.clear();
}


/******************************************************************************
*								  Properties
******************************************************************************/
std::string Location::getName() { return _name; }
std::string Location::getDescription() { return _description; }
Item* Location::getItem(std::string item_name) {
	for (auto& item : _items) { 
		if (item->getName() == item_name) { 
			return item; 
		}
	}
}
std::vector<Item*> Location::getItems() { return _items; }
Location* Location::getExit(std::string direction) { 
	if (!_exits[direction]) { return this; }
	return _exits[direction]; }
std::unordered_map<std::string, Location*> Location::getExits() { return _exits; };

void Location::setName(std::string name) { _name = name; }
void Location::setDescription(std::string description) { 
	std::replace(description.begin(), description.end(), '_', ' ');
	_description = description; 
}
void Location::setItems(std::vector<Item*> items) { _items = items; }
void Location::setExits(std::unordered_map<std::string, Location*> exits) { _exits = exits; }
void Location::setAll(std::string name, std::string description, std::vector<Item*> items,
	std::unordered_map<std::string, Location*> exits) {
	_name = name;
	_description = description;
	_items = items;
	_exits = exits;
}

/******************************************************************************
*								   Utility
******************************************************************************/
void Location::addItem(Item* item){	_items.emplace_back(item); }
void Location::addExit(std::string direction, Location* exit) {
	_exits.insert({ direction, exit });
}

void Location::showItems() {
	std::cout << "Items: " << std::endl;
	for (auto& item : _items) { item->about(); }
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
	showItems();
	showExits();
}
