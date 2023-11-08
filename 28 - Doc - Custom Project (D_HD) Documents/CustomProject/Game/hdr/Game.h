#include "Renderer.h"
#include "Window.h"

#pragma once
namespace Game {
	class Game {
	private:
		Window* _window = new Window();
		Renderer* _renderer = new Renderer();		// Todo layered rendering system
		SDL_Event* _event = nullptr;
	
	public:
		Game();
		~Game();
	
		bool init(std::string title, int x, int y, int w, int h, int flags);
		void update();
		void render(); 
		void destroy();

		inline const bool isRunning(){ return _window->isRunning(); }
	
	private:
		void handleEvents();
	};
}