#include <iostream>
#include <algorithm>
#include <string>
#include "../hdr/WorldLoader.h"

/******************************************************************************
*							    De/Constructors
******************************************************************************/
WorldLoader::WorldLoader(const std::string& file_name) : _file_name(file_name) {
	if (_file_name != "") {
		_reader.open(_file_name);
		if (!_reader.is_open()) {
			std::cout << "Err: reader couldn't open file.\n";
		}
	}

	if (_game_data == nullptr) { _game_data = new GameData(); }

	if (_entity_factory == nullptr) {
		_entity_factory = new EntityFactory(_game_data);
	}
	else {
		delete _entity_factory;
		_entity_factory = nullptr;
		_entity_factory = new EntityFactory(_game_data);
	}
}


// Don't you dare delete that fucking gamedata >:(
WorldLoader::~WorldLoader() {
	if (_reader.is_open()) { _reader.close(); }
	if (_entity_factory != nullptr) {
		delete _entity_factory;
		_entity_factory = nullptr;
	}
}


/******************************************************************************
*							    Private Methods
******************************************************************************/
/*	Reads the file and returns a vector of strings, each element containing
*	unformatted, uncommented line data from the save file.					 */
std::vector<std::string> WorldLoader::readFile() {
	std::string line;
	std::vector<std::string> save_lines;

	if (!_reader.is_open()) {
		std::cout << "Err: Reader not instanced.\n";
		return {};
	}
	else {
		while (std::getline(_reader, line)) {
			std::remove(line.begin(), line.end(), ' ');

			if (!isComment(line)) {
				std::vector<std::string> line_hack = splitSaveLine(line, ';');
				save_lines.emplace_back(line_hack[0]);
			}
		}
	}

	return save_lines;
}

/*	Takes a string and returns a vector of strings, each element a substring
*	of the original string delimited around a designated character			*/
std::vector<std::string> WorldLoader::splitSaveLine(std::string& line,
	const char delimiter) {
	int start_idx = 0, end_idx = 0;
	std::string raw_line_data = line += delimiter;
	std::vector<std::string> formatted_line_data;

	for (int idx = 0; idx <= raw_line_data.size(); idx++) {
		if (char(raw_line_data[idx]) == delimiter) {
			std::string line_datum;
			end_idx = idx;

			line_datum.append(raw_line_data, start_idx, end_idx - start_idx);
			formatted_line_data.emplace_back(line_datum);

			start_idx = ++end_idx;
		}
	}

	return formatted_line_data;
}

bool WorldLoader::isComment(const std::string& line) { return line[0] == '#'; }


/******************************************************************************
*							     Public Methods
******************************************************************************/
void WorldLoader::setSaveFile(const std::string& file_name) {
	if (!_reader.is_open()) {
		_reader.open(file_name);
		if (!_reader.is_open()) { std::cout << "Err: Bad filepath.\n"; }
	}
	else {
		_reader.close();

		_reader.open(file_name);
		if (!_reader.is_open()) { std::cout << "Err: Bad filepath.\n"; }
	}
}
/*	Reads file, constructs entities and components based of file data and
*	appends them to the relevant GameData maps.
*
*	Needs to have the filename already set in the constructor				*/
GameData* WorldLoader::loadGameData() {
	std::vector<std::string> raw_save_lines = readFile();

	if (!raw_save_lines.empty() && _entity_factory != nullptr) {
		std::vector<std::string> prefmt_entity_data;
		std::vector<std::vector<std::string>> prefmt_entity_dataset;

		// First element is the entity tag and the second is the component flag
		// and args in one big string for the component factory.
		for (auto& raw_entity_data : raw_save_lines) {
			prefmt_entity_data = splitSaveLine(raw_entity_data, ':');
			prefmt_entity_dataset.emplace_back(prefmt_entity_data);
		}

		_entity_factory->setEntityData(prefmt_entity_dataset);
		_entity_factory->constructEntities(); //Applies changes directly to GameData
	}

	return _game_data;
}
