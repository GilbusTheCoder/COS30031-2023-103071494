#include <fstream>
#include <vector>
#include "GameData.h"

#pragma once

namespace Game {
	// Instances all of the texture components from relative paths stored
	// in a file
	class SpriteLoader {
	public:
		static std::vector<SDL_Texture*> loadTextures(const std::string& filepath, SDL_Renderer* renderer);

	private:
		inline static const bool isComment(const std::string& line) { 
			return line[0] == '#'; }

		inline static void destroy(std::ifstream* reader) {
			if (reader->is_open()) reader->close(); }


		static std::ifstream setSaveFile(const std::string& filepath);
		static SDL_Texture* loadTexture(std::string& texture_path, SDL_Renderer* renderer);
	};
}

