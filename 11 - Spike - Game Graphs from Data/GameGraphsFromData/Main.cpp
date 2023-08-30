#include <iostream>
#include <vector>

class Location {
private:
	std::string _name;
	std::string _description;
	std::vector<Location*> _exits;

public:
	Location(std::string name = " ", 
		std::string description = " ", 
		std::vector<Location*> exits = {}) 
	{
		_name = name;
		_description = description;
		_exits = exits;
	}

	std::string GetName() { return _name; }
	void SetAll(std::string name, std::string description, std::vector<Location*> exits) {
		_name = name;
		_description = description;
		_exits = exits;
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
		ShowExits();
		std::cout << std::endl;
	}
};

class World {
private:
	// Wont be needed once reading from a file as we can tell when to stop
	// when there's nothing else to read.
	Location* _current_location = nullptr;
	std::vector<Location*> _locations;

public:
	World(Location* initial_location = nullptr) {
		_current_location = initial_location;
		
		if (_current_location != nullptr) {
			_locations.push_back(_current_location);
		}
		else { std::cout << "Error: No initial location given to World constructor" << std::endl; }
	}

	void AddLocation(Location* new_location) {
		_locations.push_back(new_location);
	}

	void ChangeCurrentLocation(std::string location_name) {		
		for (auto it : _locations) {
			if (it->GetName() == location_name) {
				_current_location = it;
			}
		}
	}

	// Wrapper for the current locations methods
	void ShowCurrentLocation() {
		_current_location->ShowDetails();
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

	//Forward declate the locations so they can reference each other
	Location init_location, loc1, loc2, loc3;
	//Initial setup
	init_location.SetAll("Start room", "Cold, dank and rank", { &loc1, &loc3 });
	World world(&init_location);

	//Define & add rooms
	loc1.SetAll("Location 1", "A bit sunnier", { &init_location,&loc2 });
	loc2.SetAll("Location 2", "Looks like Sullies room", { &loc1, &loc3 });
	loc3.SetAll("Location 3", "Hey, i can get back to the start from here!", { &init_location });
	

	world.AddLocation(&loc1);
	world.AddLocation(&loc2);
	world.AddLocation(&loc3);

	world.ShowCurrentLocation();

	world.ChangeCurrentLocation("Location 1");
	world.ShowCurrentLocation();
}