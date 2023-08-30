#include <iostream>
#include <vector>

class Location {
private:
	std::string _name;
	std::string _description;

	//Replace this with our item class once it's implemented in zorkish
	std::vector<std::string> _items;
	std::vector<Location*> _exits;


public:
	Location(std::string name = " ", std::string description = " ",
		std::vector<std::string> items = {}, std::vector<Location*> exits = {}) {
		_name = name;
		_description = description;
		_items = items;
		_exits = exits;
	}

	std::string GetName() { return _name; }
	void SetAll(std::string name, std::string description,
		std::vector<std::string> items, std::vector<Location*> exits) {
		_name = name;
		_description = description;
		_items = items;
		_exits = exits;
	}

	void ShowItems() {
		std::cout << "Items: " << std::endl;

		for (auto it : _items) {
			std::cout << ">> " << it << std::endl;
		}
	}

	void ShowExits() {
		std::string exit_name; 
		std::cout << "Exits: " << std::endl;
		
		for (auto it : _exits) {
			exit_name = it->GetName();
			std::cout << ">> " << exit_name << std::endl;
		}
	}

	void ShowDetails() {
		std::cout << "Room: " << _name << std::endl
			<< "Description: " << _description << std::endl;
		
		ShowItems();
		ShowExits();
	}
};

class World {
private:
	// Wont be needed once reading from a file as we can tell when to stop
	// when there's nothing else to read.
	int _world_size;
	Location* _current_location;
	
	std::vector<Location*> _locations;

	void ConstructLocations() {
		// Push our initial location to the list
		// Construct however many worlds are required, fill with rand data for now
		_locations.push_back(_current_location);
	}

public:
	/*
	World(Location* init_location, int world_size) {
		_current_location = init_location;
		_world_size = world_size;
	}*/

	World(std::vector<Location*> locations) { _locations = locations; }

	void ChangeCurrentLocation(Location* new_location) {
		_current_location = new_location;
	}

	void ShowLocations() {
		for (auto it : _locations) {
			it->ShowDetails();
		}
	}
};

int main() {
	/* Picture a 2x2 room, character will start in the bottom left
	* 
	* L1 L2
	* S  L3 
	* 
	* Testing: once the character goes into L3 they can only go to S */ 

	std::vector<Location*> locations;
	Location init_location, loc1, loc2, loc3;

	init_location.SetAll("Start room", "Cold and dank", { "Sword", "Chest" }, { &loc1, &loc3 });
	loc1.SetAll("Location 1", "A bit sunnier", { "Beach Towel", "Fork", "Paper hat" }, { &init_location,&loc2 });
	loc2.SetAll("Location 2", "Looks like Sullies room", { "bed" }, { &loc1, &loc3 });
	loc3.SetAll("Location 3", "Hey, i can get back to the start from here!", { " " }, { &init_location });

	locations.push_back(&init_location);
	locations.push_back(&loc1);
	locations.push_back(&loc2);
	locations.push_back(&loc3);

	World world(locations);
	world.ShowLocations();
}