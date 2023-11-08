#include <map>
#include "Component.h"
#include "../../Game/hdr/FileReader.h"

#pragma once

/*	Call spriteloader to get all of our sprites
*	Read texture data from a file and assign, id, type, bounds and such
*	Create a map of texture components for use in GameData */

namespace ECS {
	// Nicer way to pass texture data and defaults.
	struct TextureData {
		component_id id="zzzz";
		ComponentType type = ComponentType::C_TRANSFORM;

		SDL_Texture* sprite = nullptr;
		int x=0,y=0,w=0,h=0;
		bool render_this=false;
	};

	class TextureLoader : public Game::FileReader {
	public:
		static std::map<component_id, Texture> loadTextures(SDL_Renderer* renderer);

	private:
		static Texture loadTexture(TextureData texture_data);
	};
}
