#include "Window.h"
#include "Renderer.h"
#include "../../ECS/hdr/InteractionSystem.h"
#include <SDL_events.h>

#pragma once
namespace ECS {
	class EventHandler {
	private:
		SDL_Event* _event = nullptr;
		Game::Window* _window = nullptr;

		InteractionContext _is_context;
		InteractionSystem* _is = new InteractionSystem();

	public:
		bool init(Game::Window* window_ref, GameData* game_data_ref, 
			Game::Renderer* renderer_ref);
		
		void update();
		void destroy();
	
	private:
		void dispatchEvents();
	};
}

