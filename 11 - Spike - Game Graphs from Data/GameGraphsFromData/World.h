#pragma once
#include <iostream>
#include <fstream>
#include <vector>

#include "WorldLoader.h"
#include "Location.h"


/*	The world object will also have to act as a pseudo-interface between the save data
*	and all of the world objects. It wont have the ability to read directly from files
*	but will have the ability to take a vector of semi-formatted data from the FileReader,
*	process this more and assign its' elements to the neccessary location objects
*
*	The rules for the text file are as follows:
*		Use ';' to seperate locations
*		Use ':' to seperate location data
*		Everything after the description is an exit name
*		E.g. Name1:Description1:ExitAName:ExitBName:ExitCName;
*			 Name2:Description2:ExitAName:ExitDName:ExitZName;
*
*		Use _ as replacement for spaces. I will eventually write a function which converts
*		between the two but for right now all white space is being removed so descriptions
*		will look funny but meh.														*/

class World {
private:
	bool _is_running = true;
	std::string _save_name = "test.txt";
	WorldLoader* _reader = new WorldLoader(_save_name);

	std::vector<Location*> _locations;
	std::vector<std::string> _valid_directions = {
		"north", "n", "up", "forward",
		"east", "e", "right",
		"south", "s", "down", "back", "backwards",
		"west", "w", "left"
	};

	Location* _current_location = nullptr;

	// Any new locations are instantiated here
	std::vector<Location*> constructLocations();
	Location* getLocationByName(std::string location_name);

	std::string processDirectionInput(std::string dir);
	bool checkDirectionsValid(std::string dir);

public:
	World();
	~World();
	void update();
	void render();

	bool checkIsRunning();
	void addLocation(Location* new_location);
	void showCurrentLocation();
	void showLocations();
	void loadLocationData();

};

