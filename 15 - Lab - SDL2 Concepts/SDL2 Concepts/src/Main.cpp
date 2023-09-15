#include <SDL.h>
#include <iostream>
#include <random>

int main(int argc, char* argv[]) {
	bool is_running = true;
	int r, g, b, a;
	
	//Init SDL subsystems, window and renderer.
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Task 12 - SDL2 Concepts, Thomas Horsley 103071494",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 800, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);


	//	Set window color to green initially
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	while (is_running) {
		SDL_Event event;
		const Uint8* keystates = SDL_GetKeyboardState(NULL);
	
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) { is_running = false; }			
			if (keystates[SDL_SCANCODE_Q]) { is_running = false; }

			if (keystates[SDL_SCANCODE_R]) {
				r = std::rand() % 255;
				g = std::rand() % 255;
				b = std::rand() % 255;
				a = 128 + (std::rand() % 128);

				SDL_SetRenderDrawColor(renderer, r, g, b, a);
				SDL_RenderClear(renderer);
				SDL_RenderPresent(renderer);
			}
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	return 0;
}