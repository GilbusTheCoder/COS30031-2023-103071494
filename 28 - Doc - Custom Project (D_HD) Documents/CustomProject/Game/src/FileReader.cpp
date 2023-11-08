#include "../hdr/FileReader.h"
#include <algorithm>
#include <SDL_log.h>

std::ifstream Game::FileReader::setSaveFile(const std::string& filepath) {
	std::ifstream reader;

	reader.open(filepath);
	if (!reader.is_open()) { SDL_Log("FileReader >> Texture filepath incorrect\n"); }

	return reader;
}

std::vector<std::string> Game::FileReader::splitSaveLine(std::string& line,
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

std::string Game::FileReader::toLower(const std::string& line) {
	std::string lower_line;
	for (int idx = 0; idx < line.size(); ++idx) {
		std::string c(1, std::tolower(line[idx]));
		lower_line.append(c); }

	return lower_line;
}
