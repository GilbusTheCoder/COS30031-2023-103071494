#include "InventoryItem.h"
#include <iostream>;

InventoryItem::InventoryItem() {};
InventoryItem::InventoryItem(std::string name, std::string type, std::string description) {
	setName(name);
	setType(type);
	setDescription(description);
}

std::string InventoryItem::getName() { return _name; }
void InventoryItem::setName(std::string name) { _name = name; }
std::string InventoryItem::getType() { return _type; }
void InventoryItem::setType(std::string type) { _type = type; }
std::string InventoryItem::getDescription() { return _description; }
void InventoryItem::setDescription(std::string description) { _description = description; }

void InventoryItem::printDescription() {
	std::cout << "Name: " << _name << std::endl;
	std::cout << "Type: " << _type << std::endl;
	std::cout << "Desc: " << _description << std::endl;
};