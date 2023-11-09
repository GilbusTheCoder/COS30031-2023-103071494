#include "../hdr/RenderLayer.h"

SDL_Renderer*  ECS::RenderLayer::_renderer = nullptr;

bool ECS::RenderLayer::init(SDL_Window* window) {
	if (!window) {
		SDL_Log("RenderLayer >> No window context provided to layer\n");
		return false; }
	
	if (!_renderer) {
		_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if (!_renderer) {
			SDL_Log("Renderer >> Failed to instance renderer\n");
			return false; }	}


}
