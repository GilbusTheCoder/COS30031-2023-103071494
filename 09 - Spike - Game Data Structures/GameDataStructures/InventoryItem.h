#pragma once
#include <iostream>

class InventoryItem
{
private:
	std::string _name;
	std::string _type;
	std::string _description;

public:
	InventoryItem();
	InventoryItem(std::string name, std::string type, std::string description);

	std::string getName();
	void setName(std::string name);
	std::string getType();
	void setType(std::string type);
	std::string getDescription();
	void setDescription(std::string description);

	void printDescription();
};

