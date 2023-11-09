#include "../hdr/CompLoader.h"

std::vector<std::string> CompLoader::splitSaveLine(std::string& line, const char delimiter) {
	int start_idx = 0, end_idx = 0;
	std::string raw_line_data = line += delimiter;
	std::vector<std::string> formatted_line_data;

	for (int idx = 0; idx <= raw_line_data.size(); idx++) {
		if (char(raw_line_data[idx]) == delimiter) {
			std::string line_datum;
			end_idx = idx;

			line_datum.append(raw_line_data, start_idx, end_idx - start_idx);
			if (!line_datum.empty()) { formatted_line_data.emplace_back(line_datum); }

			start_idx = ++end_idx;
		}
	}

	return formatted_line_data;
}
