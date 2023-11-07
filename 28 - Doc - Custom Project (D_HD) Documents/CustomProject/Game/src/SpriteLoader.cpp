#include <SDL_image.h>
#include "../hdr/SpriteLoader.h"

std::vector<SDL_Texture*> Game::SpriteLoader::loadTextures(const std::string& filepath, SDL_Renderer* renderer) {
	if (filepath.empty()) {
		SDL_Log("No texture filepath provided\n");
		return { }; }

	if (!renderer) {
		SDL_Log("No texture renderer provided\n");
		return { };
	}

	std::ifstream reader = setSaveFile(filepath);
	std::vector<SDL_Texture*> textures;
	std::string texture_path;
	
	while (std::getline(reader, texture_path)) {
		if (!isComment(texture_path)) {
			SDL_Texture* new_texture = loadTexture(texture_path, renderer);
			if (new_texture) { textures.emplace_back(new_texture); }
		}
	}

	destroy(&reader);
	return textures;
}

std::ifstream Game::SpriteLoader::setSaveFile(const std::string& filepath) {
	std::ifstream reader;

	reader.open(filepath);
	if (!reader.is_open()) { SDL_Log("Texture filepath incorrect\n"); }

	return reader;
}

SDL_Texture* Game::SpriteLoader::loadTexture(std::string& texture_path,
	SDL_Renderer* renderer) {
	SDL_Surface* surface = IMG_Load(texture_path.c_str());
	
	if (!surface) {
		SDL_Log("Texture surface failed to instantiate\n");
		return nullptr; }

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (!texture) {
		SDL_Log("Failed to instance surface during loadTexture\n");
		return nullptr; }

	SDL_FreeSurface(surface);
	return texture;
}