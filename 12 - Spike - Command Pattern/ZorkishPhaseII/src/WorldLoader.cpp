#include "../header/pch.h"
#include "../header/WorldLoader.h"

//					-- Constructors --
WorldLoader::WorldLoader(std::string file_name) {
	if (file_name != "") {
		_file_name = file_name;
		_reader.open(file_name);

		if (!_reader.is_open()) { std::cout << "Can't open file!"; }
	}
}

WorldLoader::~WorldLoader() {
	if (_reader.is_open()) { _reader.close(); }
}


//					  -- Private --
bool WorldLoader::isComment(std::string string_data) {
	char comment_char = '#';

	if (string_data[0] == comment_char) {
		string_data.erase(string_data.begin(), string_data.end());
		return true;
	}
	return false;
}

std::vector<std::string> WorldLoader::splitLine(std::string string_data, char delimiter) {
	std::vector<std::string> split_strings;
	int start_idx = 0, end_idx = 0;

	for (int i = 0; i < string_data.size(); i++) {
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



//						-- Public --
void WorldLoader::openFile(std::string file_name) {
	// Some protection incase bad filename is entered. Probably redundant overengineering.
	std::string previous_file_name = _file_name;
	_file_name = file_name;

	if (_reader.is_open()) {
		_reader.close();
	}

	_reader.open(_file_name);

	if (!_reader.is_open()) {
		std::cout << "Err: can't open file '" << file_name << "'." << std::endl;
		_file_name = previous_file_name;
		_reader.open(_file_name);
	}
}


/*	1. Split the file into lines with no whitespace, ignore comments
*	2. Delimit by ':' to split the lines into elements <name, desc, items, _exits>
*	3. Return the formatted location data*/
std::vector<std::vector<std::string>> WorldLoader::getFormattedFileData() {  
	std::string raw_line;
	std::vector<std::string> unformatted_location_data = {};
	std::vector<std::vector<std::string>> formatted_location_data = {};

	// Split by line
	while (std::getline(_reader, raw_line)) {
		remove(raw_line.begin(), raw_line.end(), ' ');
		raw_line.pop_back(); // Get rid of junk value which is added by remove??? look into that

		// Check if the line is a comment if so ignore
		if (!isComment(raw_line)) {
			unformatted_location_data.push_back(raw_line);
		}
	}

	// Split each line into it's elements and add that to a 2D vector formatted like: 
	// <<'name_0', 'desc_0', 'item_name_0_0, item_name_0_1, ...', 'dir_0_0, exit_name_0_0', ...>
	// <'name_1', 'desc_1', 'item_name_1_0, item_name_1_1, ...', 'dir_1_0, exit_name_1_0', ...>...>
	for (auto unformatted_location : unformatted_location_data) {
		formatted_location_data.push_back(splitLine(unformatted_location, ':'));
	}

	return formatted_location_data;
};