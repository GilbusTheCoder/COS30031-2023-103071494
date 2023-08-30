#include <iostream>
#include <vector>
#include <fstream>
#include <string>

/*	Task: Task 11 - Spike
*	Title: Game Data From Graphs
*	Author: Thomas Horsley - 103071494
* 
*	Currently:  Working on using a file reader to instantiate the location game object
*			    and there-in the world object from a text file, could use JSON later.	
* 
*				Will probably end up making the world object more of a world "manager" 
*				class. So given this, we're giving it the ability to read and write saves
*				and it will have access to the player object.
* 
* 
*		Formatting:
*			To make life easier with the functions that I've already written we're going
*			to split the txt file using a double delimiter method.
*				* Delimit once to split the file by room
*					This will return a vector of strings
*				* Iterate through each vector and split their strings into another set 
*				  of vectors.
*				* Use this data to instantiate location objects */ 

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

		// Remove Whitespace
		remove(line.begin(), line.end(), ' ');
		line.pop_back(); // Get rid of junk value which is added by remove??? look into that

		// If the comment isn't a line, split the string and add each element to our
		// delimited_data vector.
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

/*	The world object will also have to act as a pseudo-interface between the save data
*	and all of the world objects. It wont have the ability to read directly from files
*	but will have the ability to take a vector of semi-formatted data from the FileReader,
*	process this more and assign it to the neccessary locations 
* 
*	The rules for the text file are as follows:
*		Use ';' to seperate locations
*		Use ':' to seperate location data
*		E.g. Name1:Description1:ExitAName:ExitBName:ExitCName;
*			 Name2:Description2:ExitAName:ExitDName:ExitZName; */

class World {
private:
	// Wont be needed once reading from a file as we can tell when to stop
	// when there's nothing else to read.
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

public:
	/*	1.	Initialize memory for each location and push the pointers to these
	*		locations to the locations vector
	*	2.	Let the file reader run through the save file data and return a vector
	*		of strings which of each contains the data for a location
	*			* Name
	*			* Description
	*			* Name of Exit locations seperated with : 
	*				To make sure this is consistent, the room must be named the same
	*				in the text file as it is in the code. */

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

	// Wrapper for the current locations methods
	void ShowCurrentLocation() { _current_location->ShowDetails(); }
	void ShowLocations() { for (auto it : _locations) { it->ShowDetails(); }}

	// For the assumptions made see
	void LoadLocationData() {
		//Delimiters
		char semicolon = ';';
		char colon = ':';

		std::vector<std::string> unformatted_room_data = _reader->GetLinesByDelimiter(semicolon);
		std::vector<std::vector<std::string>> formatted_room_data;

		for (auto it : unformatted_room_data) { 
			it += colon; // Add the delimiter to the end of the line
			std::vector<std::string> formatted_line = _reader->splitLine(it, colon);
			formatted_room_data.push_back(formatted_line);
		}

		for (int i = 0; i < formatted_room_data.size(); i++) {
			for (int j = 0; j < formatted_room_data[i].size(); j++) {
				std::cout << formatted_room_data[i][j] << std::endl;
			}
		}

		std::cout << "testline" << std::endl;
	}
};

int main() {
	/* Picture a 2x2 room, character will start in the bottom left
	* 
	* L1 L2
	* S  L3 
	* 
	* Testing: once the character goes into L3 they can only go to S */ 

	//Initial setup
	World world;

	world.LoadLocationData();
}