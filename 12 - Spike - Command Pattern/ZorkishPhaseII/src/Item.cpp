#include "../hdr/Item.h"

Item::Item(std::string name, std::string description, ITEM_TYPES type)
	:_name(name), _description(description), _type(type){ }

std::string Item::getName() { return _name; }
std::string Item::getDescription() { return _description; }
ITEM_TYPES Item::getType() { return _type; }
void Item::setName(std::string name) { _name = name; }
void Item::setDescription(std::string description) { _description = description; }
void Item::setType(ITEM_TYPES type) { _type = type; }

void Item::about() {
	std::cout << "Name: " << _name << std::endl;
	std::cout << "Desc: " << _description << std::endl;
	std::cout << "Type: " << _type << std::endl;
}