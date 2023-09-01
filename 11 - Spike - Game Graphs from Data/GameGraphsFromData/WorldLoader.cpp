#include "WorldLoader.h"
#include "string"

bool WorldLoader::isComment(std::string string_data) {
	remove(string_data.begin(), string_data.end(), ' ');

	if (string_data[0] == '#') {
		string_data.erase(string_data.begin(), string_data.end());
		return true;
	}
	return false;
}

std::vector<std::string> WorldLoader::processString(std::string string_data, char delimiter) {
	std::string line = string_data;
	std::vector<std::string> delimited_data;

	remove(line.begin(), line.end(), ' ');	// Remove Whitespace
	line.pop_back(); // Get rid of junk value which is added by remove??? look into that

	if (!isComment(line)) {
		delimited_data = splitLine(line, delimiter);
	}

	return delimited_data;
}

WorldLoader::WorldLoader(std::string file_name = "") {
	_file_name = file_name;

	if (_file_name == "") { std::cout << "Error: No file name supplied. "; }
	else { _reader.open(file_name); }
}

WorldLoader::~WorldLoader() { if (_reader.is_open()) { _reader.close(); } }

std::vector<std::string> WorldLoader::splitLine(std::string string_data, char delimiter) {
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

std::vector<std::string> WorldLoader::getLinesByDelimiter(char splitter) {
	char delimiter = splitter;
	std::string line;
	std::vector<std::string> formatted_strings;

	if (!_reader.is_open()) { _reader.open(_file_name); }

	while (std::getline(_reader, line)) {
		for (auto it : processString(line, delimiter)) {
			formatted_strings.push_back(it);
		}
	}

	return formatted_strings;
}

std::vector<std::string> WorldLoader::getLinesByDelimiter(char splitter, std::string string_data) {
	char delimiter = splitter;
	std::string line = string_data;
	std::vector<std::string> formatted_strings;

	if (!_reader.is_open()) { _reader.open(_file_name); }

	while (std::getline(_reader, line)) {
		for (auto it : processString(line, delimiter)) {
			formatted_strings.push_back(it);
		}
	}

	return formatted_strings;
}