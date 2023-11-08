#include <fstream>
#include <vector>

#pragma once

/*	Gives some universal functionality to all the different loader classes we
*	own. Also forces all loaders to be static classes.			*/

/*	I don't care about performance of FileReaders and Loader objects as they will
*	only be accessed and called once.							*/
namespace Game {
	class FileReader {
	protected:
		static std::ifstream setSaveFile(const std::string& filepath);
		static std::vector<std::string> splitSaveLine(std::string& line, const char delimiter);
		static std::string toLower(const std::string& line);

		inline static const bool isComment(const std::string& line) {
			return line[0] == '#';	}
	
		inline static void destroy(std::ifstream* reader) {
			if (reader->is_open()) reader->close(); }
	
	};
}