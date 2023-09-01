#pragma once
#include <iostream>
#include <fstream>
#include <vector>

class Location {
private:
	std::string _name;
	std::string _description;
	std::vector<Location*> _exits;

public:
	Location(std::string name = " ",
		std::string description = " ",
		std::vector<Location*> exits = {});

	std::string getName();
	void setName(std::string name);
	void setDescription(std::string description);
	void addExit(Location* exit);
	void setAll(std::string name, std::string description, 
		std::vector<Location*> exits);

	void showDetails();
	void showExits();
};

