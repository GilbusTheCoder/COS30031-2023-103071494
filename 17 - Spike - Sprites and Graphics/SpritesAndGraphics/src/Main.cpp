#include <iostream>
#include <random>
#include <SDL.h>

int screen_width = 1000, screen_height = 1000;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Event event;

bool display_bg = true;
SDL_Surface* screen_surface = nullptr;
SDL_Surface* bg_surface = nullptr;
SDL_Surface* tile_map_bmp = nullptr;
SDL_Texture* tile_map_texture = nullptr;

SDL_Rect tiles[4];
SDL_Rect* tile_rect = new SDL_Rect();
SDL_Rect* tile_0_mask = new SDL_Rect();
SDL_Rect* tile_1_mask = new SDL_Rect();
SDL_Rect* tile_2_mask = new SDL_Rect();

bool init() {
	bool is_success = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { is_success = false; }
	else {	window = SDL_CreateWindow("Lab 17 - Spike 'Sprites and Graphics'", 
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
			screen_width, screen_height, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		
		if (window == nullptr || renderer == nullptr) { is_success = false; }
		else { screen_surface = SDL_GetWindowSurface(window); }
	}

	return is_success;
}

bool loadBG(const char* bg_bmp_filepath) {
	bool is_success = true;
	bg_surface = SDL_LoadBMP(bg_bmp_filepath);
	
	if (bg_surface == nullptr) { is_success = false; }
	return is_success;
}

/* Math is done for one 256x256 set of 4 128x128 tiles ignoring the bot - right tile.
   It is also assumed the tiles are square. */
bool loadTileMap(const char* tm_bmp_filepath) {
	bool is_success = true;
	int tile_perimeter_px = 128;

	tile_map_bmp = SDL_LoadBMP(tm_bmp_filepath);

	if (tile_map_bmp == nullptr) { is_success = false; }
	else { 
		tile_map_texture = SDL_CreateTextureFromSurface(renderer, tile_map_bmp); 
		SDL_FreeSurface(tile_map_bmp); 
	
		for (int idx = 0; idx < 4; idx++) {
			srand(time(nullptr));
			tiles[idx].x = std::rand() % int((screen_width - (0.5 * tile_perimeter_px)));
			tiles[idx].y = std::rand() % int((screen_height - (0.5 * tile_perimeter_px)));
			tiles[idx].w = tile_perimeter_px;
			tiles[idx].h = tile_perimeter_px;
		}

		tile_0_mask->x = 0;
		tile_0_mask->y = 0;
		tile_0_mask->w = tile_perimeter_px;
		tile_0_mask->h = tile_perimeter_px;

		tile_1_mask->x = 128;
		tile_1_mask->y = 0;
		tile_1_mask->w = tile_perimeter_px;
		tile_1_mask->h = tile_perimeter_px;

		tile_2_mask->x = 0;
		tile_2_mask->y = 128;
		tile_2_mask->w = tile_perimeter_px;
		tile_2_mask->h = tile_perimeter_px;
	}

	return is_success;
}

void randomizeRectLoc(int tile_size_px) {
	tile_rect->x = std::rand() % screen_width;
	tile_rect->y = std::rand() & screen_height;
	tile_rect->w = tile_size_px;
	tile_rect->h = tile_size_px;
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
void Rendate() {
	if (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_KEYUP) {
			if (event.key.keysym.sym == SDLK_0){
				if (!display_bg) {
					if (loadBG("img/helloworld.bmp")) {
						SDL_BlitSurface(bg_surface, NULL, screen_surface, NULL);
						display_bg = false;
					}
				}
				else {
					if (loadBG("img/default_bg.bmp")) {
						SDL_BlitSurface(bg_surface, NULL, screen_surface, NULL);
						display_bg = true;
					}
				}

				SDL_UpdateWindowSurface(window);
			}

			if (event.key.keysym.sym == SDLK_1) {
				SDL_RenderCopy(renderer, tile_map_texture, tile_0_mask, tile_rect);
				randomizeRectLoc(128);
			}
			if (event.key.keysym.sym == SDLK_2) {
				SDL_RenderCopy(renderer, tile_map_texture, tile_1_mask, tile_rect);
				randomizeRectLoc(128);
			}
			if (event.key.keysym.sym == SDLK_3) {
				SDL_RenderCopy(renderer, tile_map_texture, tile_2_mask, tile_rect);
				randomizeRectLoc(128);
			}
			if (event.key.keysym.sym == SDLK_c) { SDL_RenderClear(renderer); }
		}
	}

	SDL_RenderPresent(renderer);
}


/*	1. Load an image that contains 3 seperate tiles
*	2. Define a rectangle surrounding each of the 3 tiles
*	3. On keypress, display the data contained within that rectangle to a random
*	   location using 1, 2 & 3.		*/
int main(int argc, char* argv[]) {
	bool is_running = true;

	// Init the first frame and it's data
	if (init()) {
		if (loadBG("img/helloworld.bmp") && loadTileMap("img/tilemap.bmp")) {
			SDL_BlitSurface(bg_surface, NULL, screen_surface, NULL);
			SDL_UpdateWindowSurface(window);
		}
	}
	
	// Loop
	while (is_running) {
		// Render and update :'(
		Rendate();
	}
	close(); 
	return 0; 
}