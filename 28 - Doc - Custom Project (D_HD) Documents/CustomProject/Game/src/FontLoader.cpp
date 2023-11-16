#include "../hdr/FontLoader.h"
#include <string>
Game::f_map Game::FontLoader::loadFonts(const std::string& filepath, int f_size) {
	if (filepath.empty()) {
		SDL_Log("FontLoader >> No font filepath provided\n");
		return { }; }

	int min_size = 8;
	if (f_size < min_size) {
		SDL_Log("FontLoader >> Given font size is too small\n");
		return { }; }
	
	std::ifstream reader = setSaveFile(filepath);
	std::string fontpath;
	f_map font_map;

	while (std::getline(reader, fontpath)) {
		if (!isComment(fontpath) && !fontpath.empty()) {
			TTF_Font* new_font = TTF_OpenFont(fontpath.c_str(), f_size);
			font_name new_font_name = fontNameFromFilepath(fontpath);

			font_map.insert({ new_font_name, new_font }); }
	}

	return font_map; }


Game::font_name Game::FontLoader::fontNameFromFilepath(std::string& fontpath) {
	Game::font_name name;
	int start_idx = 0, end_idx = 0;
	static int t_idx = 0;

	// Find the start of the .type
	for (int idx = 0; idx <= fontpath.size(); ++idx) {
		if (fontpath[idx] == '.') { end_idx = idx; t_idx = idx; break; }
	}

	// Now backtrack until the first '/' is found
	for (int idx = t_idx; idx >= 0; --idx) {
		if (fontpath[idx] == '/') { start_idx = idx + 1; break; }
	}

	name.append(fontpath, start_idx, end_idx - start_idx);
	name = toLower(name);
	return name;
}
