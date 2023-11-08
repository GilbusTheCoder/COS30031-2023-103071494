#include "../hdr/TextureLoader.h"
#include "../../Game/hdr/SpriteLoader.h"

std::map<ECS::component_id, ECS::Texture> ECS::TextureLoader::loadTextures(SDL_Renderer* renderer) {
	std::map<ECS::component_id, ECS::Texture> textures;
	std::map<Game::sprite_name, SDL_Texture*> sprites = 
		Game::SpriteLoader::loadSprites("Game/data/Sprite_Filepaths.txt", renderer);
	
	auto sprites_it = sprites.begin();
	int count = 0;

	for (sprites_it; sprites_it != sprites.end(); ++sprites_it) {

		TextureData texture_data = {
			sprites_it->first,
			ComponentType::C_TRANSFORM,
			sprites_it->second,
			100 + 64 * count,
			100,
			64,
			64,
			true
		};

		Texture new_texture = loadTexture(texture_data);
		textures.insert({ new_texture.id, new_texture });

		++count;
	}

	return textures;
}

ECS::Texture ECS::TextureLoader::loadTexture(TextureData texture_data) {
	Texture texture;
	SDL_Rect bounds = {
		texture_data.x,
		texture_data.y,
		texture_data.w,
		texture_data.h
	};
	
	texture.id = ECS::component_id(texture_data.id);
	texture.type = texture_data.type;

	texture.texture = texture_data.sprite;
	texture.bounds = bounds;
	texture.render_this = texture_data.render_this;

	return texture; }