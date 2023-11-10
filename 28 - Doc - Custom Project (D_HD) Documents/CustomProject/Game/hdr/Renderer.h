#include "GameData.h"
#include "RenderLayer.h"

#pragma once
namespace Game {
	class Renderer {
	private:
		std::vector<ECS::RenderLayer*> _render_layers;

	public:
		bool init(SDL_Window* window, ECS::GameData* game_data);
		void destroy(); 
	
		void update();
		void render();

		inline SDL_Renderer* getRenderer() {
			if (!_render_layers.empty()) { return _render_layers[0]->getRenderer(); }
		}
	};
}

