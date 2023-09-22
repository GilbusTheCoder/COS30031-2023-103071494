#include <unordered_map>
#include "Item.h"
#pragma once

class Location {
private:
	std::string _name;
	std::string _description;
	std::unordered_map<std::string, Location*> _exits;

public:
	Location(std::string name = "", std::string description = "",
		std::unordered_map<std::string, Location*> = {});

	std::string getName();
	std::string getDescription();
	Location* getExit(std::string direction);
	std::unordered_map<std::string, Location*> getExits();

	void setName(std::string name);
	void setDescription(std::string description);
	void setExits(std::unordered_map<std::string, Location*> exits);
	void setAll(std::string name, std::string description, std::unordered_map<std::string, Location*> exits);

	void addExit(std::string direction, Location* exit);
	void showExits();
	void about();
};

