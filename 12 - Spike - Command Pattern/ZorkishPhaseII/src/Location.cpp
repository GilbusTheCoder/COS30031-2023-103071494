#include "../header/Location.h"
#include "../header/pch.h"

Location::Location(std::string name,
	std::string description,
	std::unordered_map<std::string, Item*> items,
	std::unordered_map<std::string, Location*> exits) {
	_name = name;
	_description = description;
	_items = items;
	_exits = exits;
}

// Need C++ 17 or newer for this map search magic to work.
Location::~Location() {
	if (!_items.empty()) {
		for (auto& [item_name, item] : _items) {
			delete item;
		}
	}
	
	if (!_exits.empty()) {
		for (auto& [direction, location] : _exits) {
			delete location;
		}
	}

	_items.clear();
	_exits.clear();
}

std::string Location::getName() { return _name; }
std::string Location::getDescription() { return _description; }
std::unordered_map<std::string, Item*> Location::getItems() { return _items; }
std::unordered_map<std::string, Location*> Location::getExits() { return _exits; }

Location* Location::getExitByDir(std::string direction) {
	return _exits[direction];
}

Item* Location::getItemByName(std::string name) { return _items[name]; }

void Location::setName(std::string name) { _name = name; }
void Location::setDescription(std::string description) {
	std::replace(description.begin(), description.end(), '_', ' ');
	_description = description;
}

void Location::addItem(std::string item_name, Item* item_ptr) {
	_items.insert(std::pair<std::string, Item*>(item_name, item_ptr));
}
void Location::addExit(std::string direction, Location* exit) {
	_exits.insert({ direction, exit });
}

void Location::setAll(std::string name, std::string description,
	std::unordered_map<std::string, Item*> items,
	std::unordered_map<std::string, Location*> exits) {
	_name = name;
	_description = description;
	_items = items;
	_exits = exits;
}

void Location::showItems() {
	std::cout << "Items: " << std::endl;
	for (auto& [item_name, item] : _items) {	
		std::cout << ">> " << item->getName() << std::endl;
	}
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
