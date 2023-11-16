#include "FileReader.h"
#include <SDL_ttf.h>
#include <map>

#pragma once
namespace Game {
	typedef std::string font_name;
	typedef std::map<font_name, TTF_Font*> f_map;
	
	class FontLoader : public FileReader {
	public:
		static f_map loadFonts(const std::string& filepath, int f_size);
	
	private:
		static font_name fontNameFromFilepath(std::string& fontpath);
	};
}

