#pragma once
#include "pch.h"
#include "Items.h"

class Location {
private:
	std::string _name;
	std::string _description;
	std::unordered_map<std::string, Item*> _items;
	std::unordered_map<std::string, Location*> _exits;

public:
	Location(std::string name = " ",
		std::string description = " ",
		std::unordered_map<std::string, Item*> items = {},
		std::unordered_map<std::string, Location*> exits = {});

	// Because each location will contain a deep copy of item and exit data
	// we need to clean it up.
	~Location();

	// Beeeeg list of getters and setters
	std::string getName();
	std::string getDescription();
	Item* getItemByName(std::string name);
	std::unordered_map<std::string, Item*> getItems();
	Location* getExitByDir(std::string direction);
	std::unordered_map<std::string, Location*> getExits();

	void setName(std::string name);
	void setDescription(std::string description);
	void addItem(std::string item_name, Item* item_ptr);
	void addExit(std::string direction, Location* exit);
	void setAll(std::string name, std::string description,
		std::unordered_map<std::string, Item*> items,
		std::unordered_map<std::string, Location*> exits);

	// Show functionality left public.
	void showItems();
	void showExits();
	void showDetails();
};