#include "string"
#include "Renderer.h"

#pragma once
namespace Game {
	class Game {
	private:
		bool _is_running = false;
	
		SDL_Window* _window = nullptr;
		SDL_Event* _event = nullptr;
	
		Renderer* _renderer = new Renderer();		// Todo make rendering system
	
	public:
		Game();
		~Game();
	
		bool init(std::string title, int x, int y, int w, int h, bool fullscreen);
		void update();
		void render(); 
		void destroy();
	
		inline bool isRunning() { return _is_running; }
	
	private:
		void handleEvents();
	};
}