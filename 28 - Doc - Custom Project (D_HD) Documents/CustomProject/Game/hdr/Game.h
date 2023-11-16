#include "Window.h"
#include "Renderer.h"
#include "EventHandler.h"
#include "GameData.h"

#pragma once
namespace Game {
	class Game {
	private:
		ECS::GameData* _game_data = nullptr;

		Window* _window = new Window();
		Renderer* _renderer = new Renderer();		// Todo layered rendering system
		ECS::EventHandler* _event_handler = new ECS::EventHandler();
	
	public:
		Game();
		~Game();
	
		bool init(std::string title, int x, int y, int w, int h, int flags);
		void update();
		void render(); 
		void destroy();

		inline const bool isRunning(){ return _window->isRunning(); }

	private:
		bool initRenderer(SDL_Window* window);
	};
}