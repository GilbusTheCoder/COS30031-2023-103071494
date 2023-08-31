#include <iostream>
#include <vector>
#include <fstream>
#include <string>

/*	Task: Task 11 - Spike
*	Title: Game Data From Graphs
*	Author: Thomas Horsley - 103071494
* 
*	Completed:  Working on using a file reader to instantiate the location game object
*			    and there-in the world object from a text file, could use JSON later.	
* 
*				Will probably end up making the world object more of a world "manager" 
*				class. So given this, we're giving it the ability to read and write saves
*				and it will have access to the player object.
* 
* 
*		Formatting:
*			To make life easier with the functions that I've already written we're going
*			to split the txt file using a double delimiter tech.
*				* Delimit once to split the file by location
*					This will return a vector of strings
*				* Iterate through each vector and split their strings into another set 
*				  of vectors.
*				* Use this data to instantiate location objects 
* 
*	Summary:
*		So I don't really like this code to be honest. It works yes but instantiation of
*		locations is a really fickle fucker. Additionally the order of the location data
*		must be the same as the order of the locations in the vector. This is an issue for
*		now as the program doesn't write its own save files. Cuz i wrote it and it's stoop.
* 
*		World has a set of location pointers. It can read from a file and assign the input
*		data to the locations.
* 
*		Next step is to chop this up into class files for organisation and shove it into 
*		zorkish.......... this is going to be fun and easy :)
*/ 

class FileReader {
private:
	std::string _file_name;
	std::ifstream _reader;

	bool isComment(std::string string_data) {
		remove(string_data.begin(), string_data.end(), ' ');

		if (string_data[0] == '#') { 
			string_data.erase(string_data.begin(), string_data.end());
			return true; 
		}
		return false;
	}

	std::vector<std::string> ProcessString(std::string string_data, char delimiter) {
		std::string line = string_data;
		std::vector<std::string> delimited_data;

		remove(line.begin(), line.end(), ' ');	// Remove Whitespace
		line.pop_back(); // Get rid of junk value which is added by remove??? look into that

		if (!isComment(line)) {
			delimited_data = splitLine(line, delimiter);
		}

		return delimited_data;
	}

public:
	FileReader(std::string file_name = "") {
		_file_name = file_name;

		if (_file_name == "") { std::cout << "Error: No file name supplied. "; }
		else { _reader.open(file_name); }
	}

	~FileReader() {	if (_reader.is_open()) { _reader.close(); }}

	std::vector<std::string> splitLine(std::string string_data, char delimiter) {
		std::vector<std::string> split_strings;
		int start_idx = 0, end_idx = 0;

		for (int i = 0; i <= string_data.size(); i++) {
			if ((char)string_data[i] == delimiter) {
				std::string delimited_data;
				end_idx = i;
				delimited_data.append(string_data, start_idx, end_idx - start_idx);
				split_strings.push_back(delimited_data);

				start_idx = end_idx + 1;
			}
		}

		return split_strings;
	}

	std::vector<std::string> GetLinesByDelimiter(char splitter) {
		char delimiter = splitter;
		std::string line;
		std::vector<std::string> formatted_strings;

		if (!_reader.is_open()) { _reader.open(_file_name); }

		while (std::getline(_reader, line)) {
			for (auto it : ProcessString(line, delimiter)) {
				formatted_strings.push_back(it);
			}
		}

		return formatted_strings;
	}

	std::vector<std::string> GetLinesByDelimiter(char splitter, std::string string_data) {
		char delimiter = splitter;
		std::string line = string_data;
		std::vector<std::string> formatted_strings;

		if (!_reader.is_open()) { _reader.open(_file_name); }

		while (std::getline(_reader, line)) {
			for (auto it : ProcessString(line, delimiter)) {
				formatted_strings.push_back(it);
			}
		}

		return formatted_strings;
	}
};

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
	
	void setName(std::string name) { _name = name; }
	void setDescription(std::string description) { _description = description; }
	void addExit(Location* exit) { _exits.push_back(exit); }
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
		ShowExits(); std::cout << std::endl;
	}
};

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
*		will look funny but meh.	*/

class World {
private:
	std::string _save_name = "test.txt";
	FileReader* _reader = new FileReader(_save_name);
	
	Location* _current_location = nullptr;
	std::vector<Location*> _locations;

	// Any new locations are instantiated here
	std::vector<Location*> ConstructLocations() {
		std::vector<Location*> locations;

		//Allocate Memory for rooms
		Location* lounge_room = new Location();
		Location* courtyard = new Location();
		Location* bedroom = new Location();
		Location* backyard = new Location();

		//Push those pointers to _locations
		locations.push_back(lounge_room);
		locations.push_back(courtyard);
		locations.push_back(bedroom);
		locations.push_back(backyard);

		return locations;
	}

	Location* getLocationByName(std::string location_name) {
		for (auto location : _locations) {
			if (location->GetName() == location_name) { return location; }
		}
	}

public:
	/*	1.	Initialize memory for each location and push the pointers to these
	*		locations to the locations vector
	*	2.	Let the file reader run through the save file data and return a vector
	*		of strings each of which contains the data for a location
	*			* Name
	*			* Description
	*			* Name of Exit locations seperated with : 
	*				To make sure this is consistent, the room must be named the same
	*				in the text file as it is in the code yes this is case sensitive.	*/

	World() {
		_locations = ConstructLocations();

		if (_current_location != nullptr) {
			_locations.push_back(_current_location);
		}
		else { std::cout << "Error: No initial location given to World constructor" << std::endl; }
	}

	void AddLocation(Location* new_location) { _locations.push_back(new_location); }

	void ChangeCurrentLocation(std::string location_name) {		
		for (auto it : _locations) {
			if (it->GetName() == location_name) { _current_location = it; }
		}
	}

	// Wrappers for the current locations methods
	void ShowCurrentLocation() { _current_location->ShowDetails(); }
	void ShowLocations() { for (auto it : _locations) { it->ShowDetails(); }}


	/*	Here is a funny function. This will load everything except exit data into a location.
	*	The exit data will be done on a second pass as the structure requires the location to 
	*	own a name in to search it in the vector.	*/
	void LoadLocationData() {
		//Delimiters
		char first_pass_delim = ';';
		char second_pass_delimiter = ':';

		std::vector<std::string> unformatted_room_data = _reader->GetLinesByDelimiter(first_pass_delim);
		std::vector<std::vector<std::string>> formatted_room_data;

		for (auto room_data_set : unformatted_room_data) { 
			room_data_set += second_pass_delimiter; // Add the delimiter to the end of the line
			std::vector<std::string> formatted_line = _reader->splitLine(room_data_set, second_pass_delimiter);
			formatted_room_data.push_back(formatted_line);
		}

		for (int room_idx = 0; room_idx < formatted_room_data.size(); room_idx++) {
			_locations[room_idx]->setName(formatted_room_data[room_idx][0]);
			_locations[room_idx]->setDescription(formatted_room_data[room_idx][1]);
			}

		// It's assumed that the locations in the load file are in the same order as in the 
		// _locations vector.
		for (int room_idx = 0; room_idx < formatted_room_data.size(); room_idx++) {
			for (int exit_idx = 2; exit_idx < formatted_room_data[room_idx].size(); exit_idx++) {
				_locations[room_idx]->addExit(getLocationByName(formatted_room_data[room_idx][exit_idx]));
			} 
		}
	}
};

int main() {
	//Ahhhhhhh what a nice clean main :)
	World world;

	world.LoadLocationData();
	world.ShowLocations();
}