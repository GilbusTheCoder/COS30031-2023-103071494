#include <string>
#include "../hdr/WorldLoader.h"

/******************************************************************************
*							    De/Constructors
******************************************************************************/
WorldLoader::WorldLoader(std::string file_name)
	:_file_name(file_name){
	if (_file_name == "") { std::cout << "Err: No filename supplied." << std::endl; }
	else { _reader.open(_file_name); }
}

WorldLoader::~WorldLoader() { if (_reader.is_open()) { _reader.close(); } };


/******************************************************************************
*								  Properties
******************************************************************************/
std::vector<std::vector<Location*>> WorldLoader::getWorldData() {
	return _world_data; }


/******************************************************************************
*								   Utility
******************************************************************************/
bool WorldLoader::isComment(const std::string line) {
	std::string string_data = line;
	
	if (string_data[0] == '#') { return true; }
	return false;	
}

std::vector<std::string> WorldLoader::splitSaveLine(const std::string line, 
	const char delimiter) {
	int start_idx = 0, end_idx = 0;
	std::string line_datum;
	std::string raw_line_data = line;
	std::vector<std::string> formatted_line_data;

	for (int idx = 0; idx <= raw_line_data.size(); idx++) {
		if (char(raw_line_data[idx]) == delimiter) {
			end_idx = idx;
			line_datum.append(raw_line_data, start_idx, end_idx - start_idx);
			formatted_line_data.emplace_back(line_datum);

			start_idx = end_idx++;
		}
	}

	return formatted_line_data;
}

std::vector<std::string> WorldLoader::pullSaveData() {
	std::string line;
	std::vector<std::string> lines = {};

	if (!_reader.is_open() && _file_name != "") { _reader.open(_file_name); }
	if (_reader.is_open()) {
		while (std::getline(_reader, line)) {
			// Remove Whitespace
			remove(line.begin(), line.end(), ' ');
			line.pop_back();

			if (!isComment(line)) {
				lines.emplace_back(line);
			}
		}
	}

	return lines;
}

void WorldLoader::processSaveData(){ 
	std::vector<std::string> raw_save_data = pullSaveData();

	if (!raw_save_data.empty()) {
		for (auto save_set : raw_save_data) {
			_prelim_world_data.emplace_back(splitSaveLine(save_set, ';'));
		}
	}
}