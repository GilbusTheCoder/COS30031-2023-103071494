#pragma once
#include <iostream>
#include <fstream>
#include <vector>

class WorldLoader
{
private:
	std::string _file_name;
	std::ifstream _reader;

	bool isComment(std::string string_data);
	std::vector<std::string> processLineInput(std::string string_data, char delimiter);

public:
	WorldLoader(std::string file_name = "");
	~WorldLoader();

	std::vector<std::string> splitLine(std::string string_data, char delimiter);
	std::vector<std::string> getLinesByDelimiter(char splitter);
	std::vector<std::string> getLinesByDelimiter(char splitter, std::string string_data);

};

