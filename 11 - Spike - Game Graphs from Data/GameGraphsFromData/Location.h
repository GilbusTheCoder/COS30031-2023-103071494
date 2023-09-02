#pragma once
#include <iostream>
#include <fstream>
#include <unordered_map>

class Location {
private:
	std::string _name;
	std::string _description;
	std::unordered_map<std::string, Location*> _exits;

public:
	Location(std::string name = " ",
		std::string description = " ",
		std::unordered_map<std::string, Location*> exits = {});

	std::string getName();
	std::string getDescription();
	Location* getExit(std::string direction);
	std::unordered_map<std::string, Location*> getExits();

	void setName(std::string name);
	void setDescription(std::string description);
	void addExit(std::string direction, Location* exit);
	void setAll(std::string name, std::string description, 
		std::unordered_map<std::string, Location*> exits);

	void showDetails();
	void showExits();
};

