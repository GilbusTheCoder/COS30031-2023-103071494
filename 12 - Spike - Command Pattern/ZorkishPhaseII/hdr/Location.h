#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Item.h"

class Location {
private:
	std::string _name;
	std::string _description;
	std::vector<Item*> _items;
	std::unordered_map<std::string, Location*> _exits;

public:
	Location(std::string name = "", std::string description = "",
		std::vector<Item*> items = {},
		std::unordered_map<std::string, Location*> = {});
	~Location();

	std::string getName();
	std::string getDescription();
	Item* getItem(std::string item_name);
	std::vector<Item*> getItems();
	Location* getExit(std::string direction);
	std::unordered_map<std::string, Location*> getExits();

	void setName(std::string name);
	void setDescription(std::string description);
	void setItems(std::vector<Item*> items);
	void setExits(std::unordered_map<std::string, Location*> exits);
	void setAll(std::string name, std::string description, std::vector<Item*> items, 
		std::unordered_map<std::string, Location*> exits);

	void addItem(Item* item);
	void addExit(std::string direction, Location* exit);
	void showItems();
	void showExits();
	void about();
};

