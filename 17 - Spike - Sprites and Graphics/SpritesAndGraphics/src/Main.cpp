#include <iostream>
#include <random>
#include <SDL.h>

/*	Task:	17 - Spike
*	Title:	Sprites and Graphics
*	Author:	Thomas Horsley
*	Date:	20/09/23
* 
*	I wrote this functionally as when we're concerned with demonstration I find
*	the functional stuff easier to extrapolate into other projects. 
*	Additionally I love overengineering tf out of classes.					
*
*	Full truth though, this code is pretty grott...							*/

int screen_width = 1000, screen_height = 1000;
SDL_Window* window = nullptr;				// Freed in close()
SDL_Renderer* renderer = nullptr;			// Freed in close()
SDL_Event event;							// Stack allocated

bool display_bg = true;
SDL_Surface* screen_surface = nullptr;		// Freed when window gets destroyed
SDL_Surface* bg_surface = nullptr;			// Freed in loadBG()
SDL_Texture* bg_texture = nullptr;			// Freed in close()
SDL_Rect* bg_mask = nullptr;				// Freed in close()
SDL_Rect* bg_rect = nullptr;

SDL_Surface* tilemap_surface = nullptr;		// Freed in loadTileMap()
SDL_Texture* tilemap_texture = nullptr;		// Freed in close()
SDL_Rect* tile_rect = new SDL_Rect();		//  /
SDL_Rect* tile_0_mask = new SDL_Rect();		// |   Freed in 
SDL_Rect* tile_1_mask = new SDL_Rect();		// |   close()
SDL_Rect* tile_2_mask = new SDL_Rect();		//  \				

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
	
	if (bg_surface == nullptr) { return !is_success; }
	bg_texture = SDL_CreateTextureFromSurface(renderer, bg_surface);

	bg_rect = new SDL_Rect();
	bg_rect->x = 0;
	bg_rect->y = 0;
	bg_rect->w = screen_width;
	bg_rect->h = screen_height;

	// We like our memory here
	SDL_FreeSurface(bg_surface);
	bg_surface = nullptr;


	return is_success;
}

/* Math is done for one 256x256 set of 4 128x128 tiles ignoring the bot - right tile.
   It is also assumed the tiles are square. */
bool loadTileMap(const char* tm_bmp_filepath) {
	bool is_success = true;
	int tile_perimeter_px = 128;

	tilemap_surface = SDL_LoadBMP(tm_bmp_filepath);
	if (tilemap_surface == nullptr) { return !is_success; }
	tilemap_texture = SDL_CreateTextureFromSurface(renderer, tilemap_surface); 

	// Don't need the surface anymore as the data is copied in the texture
	SDL_FreeSurface(tilemap_surface); 
	tilemap_surface = nullptr;

	// Chop the texture into rectangles which can be used to create stuff
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
	
	return is_success;
}

void randomizeRectLoc(int tile_size_px) {
	int rect_perim_px = tile_size_px;

	tile_rect->x = std::rand() % screen_width;
	tile_rect->y = std::rand() & screen_height;
	tile_rect->w = rect_perim_px;
	tile_rect->h = rect_perim_px;
}

void close() {
	// Destroy heap objects using SDL methods
	SDL_DestroyTexture(bg_texture);
	SDL_DestroyTexture(tilemap_texture);
	SDL_DestroyWindow(window);

	// No sdl destroy rect method?
	if (bg_mask != nullptr) { delete bg_mask; }
	if (bg_rect != nullptr) { delete bg_rect; }
	if (tile_rect != nullptr) { delete tile_rect; }
	if (tile_0_mask != nullptr){ delete tile_0_mask; }
	if (tile_1_mask != nullptr){ delete tile_1_mask; }
	if (tile_2_mask != nullptr){ delete tile_2_mask;}

	// Set our global garbage to null
	if (bg_surface != nullptr) { bg_surface = nullptr; }
	if (tilemap_texture != nullptr) { tilemap_texture = nullptr; };
	if (window != nullptr) { window = nullptr; }

	SDL_Quit(); 
}

//	I LOVE THIS CODE IT LOOKS VERY GOOD!
/*	Built the render / update / input handler function as there's really not a whole
*	lot going on here		*/
bool Rendate() {
	if (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_KEYUP) {
			if (event.key.keysym.sym == SDLK_0){
				if (!display_bg) {	
					// get rid of old drawings which would be lost anyways
					SDL_RenderClear(renderer);
					SDL_RenderCopy(renderer, bg_texture, bg_mask, bg_rect);
					display_bg = !display_bg;
				}
				else { SDL_RenderClear(renderer);
					   display_bg = !display_bg; }

				SDL_UpdateWindowSurface(window);
			}

			if (event.key.keysym.sym == SDLK_1) {
				SDL_RenderCopy(renderer, tilemap_texture, tile_0_mask, tile_rect);
				randomizeRectLoc(128);
			}
			if (event.key.keysym.sym == SDLK_2) {
				SDL_RenderCopy(renderer, tilemap_texture, tile_1_mask, tile_rect);
				randomizeRectLoc(128);
			}
			if (event.key.keysym.sym == SDLK_3) {
				SDL_RenderCopy(renderer, tilemap_texture, tile_2_mask, tile_rect);
				randomizeRectLoc(128);
			}
			if (event.key.keysym.sym == SDLK_c) { SDL_RenderClear(renderer); }
			if (event.key.keysym.sym == SDLK_q) { return false; }
		}
	}

	SDL_RenderPresent(renderer);
	return true;
}


/*	1. Load an image that contains 3 seperate tiles
*	2. Define a rectangle surrounding each of the 3 tiles
*	3. On keypress, display the data contained within that rectangle to a random
*	   location using 1, 2 & 3.		*/
int main(int argc, char* argv[]) {
	// Init the first frame and it's data
	if (init()) {
		if (loadBG("img/helloworld.bmp") && loadTileMap("img/tilemap.bmp")) {
			bool is_running = true;
			while (is_running) { is_running = Rendate();	}
			close(); 
		}
	}	
	return 0; 
}