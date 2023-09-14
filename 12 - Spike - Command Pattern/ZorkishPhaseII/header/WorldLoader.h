#pragma once
#include <fstream>
#include "pch.h"

/*	Returns a vector of strings to the relevant state, from this the state can 
*	assign the values during load time	*/

class WorldLoader
{
private:
	std::string _file_name;
	std::ifstream _reader;

	bool isComment(std::string string_data);
	std::vector<std::string> splitLine(std::string string_data, char delimiter);

public:
	WorldLoader(std::string file_name = "");
	~WorldLoader();

	void openFile(std::string file_name);

	// Split each line into it's elements and add that to a 2D vector formatted like: 
	// <<'name_0', 'desc_0', 'item_name_0_0, item_name_0_1, ...', 'dir_0_0, exit_name_0_0', ...>
	// <<'name_1', 'desc_1', 'item_name_1_0, item_name_1_1, ...', 'dir_1_0, exit_name_1_0', ...>...>
	std::vector<std::vector<std::string>> getFormattedFileData();
};