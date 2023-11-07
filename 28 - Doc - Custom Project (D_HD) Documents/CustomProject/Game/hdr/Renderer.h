#include <SDL.h>
#include <vector>
#pragma once

namespace Game {
	class Renderer {
	private:
		SDL_Renderer* _renderer = nullptr;
		std::vector<SDL_Texture*> _textures;
	
	public:
		bool init(SDL_Window* window);
		void destroy(); 
	
	
		void update();
		void render();
	
	 	inline SDL_Renderer* getRenderer() { return _renderer; }
	};
}

