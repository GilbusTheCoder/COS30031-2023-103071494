#include "SpriteLoader.h"
#include "../../ECS/hdr/Component.h"
#pragma once

namespace Game {
	class Renderer {
	private:
		SDL_Renderer* _renderer = nullptr;
		std::map<ECS::component_id, ECS::Texture> _textures;
	
	public:
		bool init(SDL_Window* window);
		void destroy(); 
	
		void update();
		void render();
	
	 	inline SDL_Renderer* getRenderer() { return _renderer; }
	};
}

