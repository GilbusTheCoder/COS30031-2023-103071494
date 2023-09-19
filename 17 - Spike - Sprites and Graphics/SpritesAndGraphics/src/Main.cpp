#include <iostream>
#include <SDL.h>

SDL_Window* window = NULL;
SDL_Surface* screen_surface = NULL;
SDL_Surface* bg_surface = NULL;
SDL_Event event;
bool display_bg = true;

bool init() {
	bool is_success = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { is_success = false; }
	else {	window = SDL_CreateWindow("Lab 17 - Spike 'Sprites and Graphics'", 
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
			1000, 1000, SDL_WINDOW_SHOWN);
		
		if (window == nullptr) { is_success = false; }
		else { screen_surface = SDL_GetWindowSurface(window); }
	}

	return is_success;
}

bool loadBG(const char* filepath) {
	bool is_success = true;

	bg_surface = SDL_LoadBMP(filepath);
	if (bg_surface == nullptr) { is_success = false; }

	return is_success;
}

void close() {
	SDL_FreeSurface(bg_surface);
	SDL_DestroyWindow(window);
	bg_surface = nullptr;
	window = nullptr;

	//SDL_FreeSurface(screen_surface);
	//screen_surface is handled by closing the window
	//screen_surface = NULL;

	SDL_Quit(); 
}

// I LOVE THIS CODE IT LOOKS VERY GOOD!
void handleInput() {
	if (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_KEYUP) {
			if (event.key.keysym.sym == SDLK_0){
				if (display_bg) {
					if (loadBG("img/default_bg.bmp")) {
						SDL_BlitSurface(bg_surface, NULL, screen_surface, NULL);
						display_bg = false;
					}
				}
				else {
					if (loadBG("img/helloworld.bmp")) {
						SDL_BlitSurface(bg_surface, NULL, screen_surface, NULL);
						display_bg = true;
					}
				}

				SDL_UpdateWindowSurface(window);
			}
		}
	}
}


int main(int argc, char* argv[]) {
	bool is_running = true;

	// Init the first frame and it's data
	if (init()) {
		if (loadBG("img/helloworld.bmp")) {
			SDL_BlitSurface(bg_surface, NULL, screen_surface, NULL);
			SDL_UpdateWindowSurface(window);
		}
	}
	
	// Loop
	while (is_running) {
		handleInput();
	}
	close(); 
	return 0; 
}