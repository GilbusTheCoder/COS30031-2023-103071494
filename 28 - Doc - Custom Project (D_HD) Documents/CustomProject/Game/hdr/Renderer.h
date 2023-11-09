#include "../../ECS/hdr/ECConstructor.h"
#include "GameData.h"

#pragma once
namespace Game {
	class Renderer {
	private:
		SDL_Renderer* _renderer = nullptr;
		std::map<ECS::component_id, ECS::Texture> _textures;
	
	public:
		bool init(SDL_Window* window, ECS::GameData* game_data);
		void destroy(); 
	
		void update();
		void render();

		inline void setTextures(std::map<ECS::component_id, ECS::Texture> textures) { _textures = textures; }
	 	inline SDL_Renderer* getRenderer() { return _renderer; }
	};
}

