#include <iostream>
#include "../hdr/Window.h"

Window::Window(const std::string& title, int width, int height) 
	: _title(title), _width(width), _height(height) { 
	_is_running = init(); }

Window::~Window() { 
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit(); }



void Window::update(SDL_Event* event) {
	if (event->type == SDL_QUIT) { _is_running = false; }
	else if (event->type == SDL_KEYDOWN) {
		if (event->key.keysym.sym == SDLK_ESCAPE) { _is_running = false; }
	}
}

// Draws a rectangle
void Window::clear() const {
	SDL_RenderPresent(_renderer);	// Show changes
	SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderClear(_renderer);		// Apply background changes
}



bool Window::init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr <<"Bad SDL_Video init.\n";
		return 0;}

	_window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, _width, _height, 0);
	if (!_window) {
		std::cerr << "Bad window instantiation.\n";
		return 0; }

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (!_renderer) {
		std::cerr << "Bad renderer instantiation.\n";
		return 0; }

	return true;
}
