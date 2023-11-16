#include "../hdr/Window.h"

bool Game::Window::init(std::string title, int xpos, int ypos, int width, int height, int flags) {
	_title = title.c_str();
	_x = xpos;
	_y = ypos;
	_w = width;
	_h = height;
	_flags = flags;

	if (SDL_Init(SDL_INIT_VIDEO) > 0) {
		SDL_Log("Window >> Failed to initialize SDL Video subystem\n");
		return false; }

	_window = SDL_CreateWindow(_title, _x, _y, _w, _h, _flags);
	if (!_window) {	
		SDL_Log("Window >> Failed to initialize Window\n"); 
		return false; }

	return _is_running = true; }


void Game::Window::destroy() {
	SDL_DestroyWindow(_window);
	_window = nullptr; }