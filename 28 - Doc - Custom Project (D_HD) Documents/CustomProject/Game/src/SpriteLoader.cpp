#include "../hdr/SpriteLoader.h"
#include <map>
#include <string>
#include <SDL_image.h>

Game::sprite_map Game::SpriteLoader::loadSprites(const std::string& filepath, SDL_Renderer* renderer)
{
	if (filepath.empty()) {
		SDL_Log("SpriteLoader >> No texture filepath provided\n");
		return { };
	}

	if (!renderer) {
		SDL_Log("SpriteLoader >> No texture renderer provided\n");
		return { };
	}

	std::ifstream reader = setSaveFile(filepath);
	std::map<sprite_name, SDL_Texture*> sprites;
	std::string texture_path;

	while (std::getline(reader, texture_path)) {
		if (!isComment(texture_path) && !texture_path.empty()) {
			SDL_Texture* new_sprite = loadSprite(texture_path, renderer);
			sprite_name new_name = spriteNameFromFilepath(texture_path);
			new_name = toLower(new_name);
			
			sprites.insert({ new_name, new_sprite });
		}
	}

	destroy(&reader);
	return sprites;
}

SDL_Texture* Game::SpriteLoader::loadSprite(std::string& sprite_path,
	SDL_Renderer* renderer) {
	SDL_Surface* surface = IMG_Load(sprite_path.c_str());
	
	if (!surface) {
		SDL_Log("SpriteLoader >> Texture surface failed to instantiate\n");
		return nullptr; }

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (!texture) {
		SDL_Log("SpriteLoader >> Failed to instance surface during loadTexture\n");
		return nullptr; }

	SDL_FreeSurface(surface);
	return texture;
}

Game::sprite_name Game::SpriteLoader::spriteNameFromFilepath(std::string& sprite_path) {
	Game::sprite_name name;
	int start_idx = 0, end_idx = 0;
	static int t_idx = 0;

	// Find the start of the .type
	for (int idx = 0; idx <= sprite_path.size(); ++idx) {
		if (sprite_path[idx] == '.') { end_idx = idx; t_idx = idx; break; } }

	// Now backtrack until the first '/' is found
	for (int idx = t_idx; idx >= 0; --idx) {
		if (sprite_path[idx] == '/') { start_idx = idx + 1; break; } }

	name.append(sprite_path, start_idx, end_idx - start_idx);
	name = toLower(name);
	return name;
}
