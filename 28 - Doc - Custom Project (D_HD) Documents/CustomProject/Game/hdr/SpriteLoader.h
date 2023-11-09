#include "FileReader.h"
#include <map>
#include <SDL.h>

#pragma once
namespace Game {
	typedef std::string sprite_name;
	typedef std::map<std::string, SDL_Texture*> sprite_map;

	// Instances all of the texture components from relative paths stored
	// in a file
	class SpriteLoader : public FileReader {
	public:
		static std::map<sprite_name, SDL_Texture*> loadSprites(const std::string& filepath, SDL_Renderer* renderer);
	
	private:
		static SDL_Texture* loadSprite(std::string& sprite_path, SDL_Renderer* renderer);
		static sprite_name spriteNameFromFilepath(std::string& sprite_path);
	};
}	

