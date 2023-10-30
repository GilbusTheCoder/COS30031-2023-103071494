#include "../hdr/Rect.h"
#include <iostream>

Rect::Rect(Window* window, int w, int h, int x, int y, 
	int r, int g, int b, int a) : _w(w), _h(h), _x(x), _y(y),
								  _r(r), _g(g), _b(b), _a(a) {

	_renderer = window->getRenderer();
	if (_renderer == nullptr) { std::cerr << "Rect not given valid renderer.\n"; }
}

void Rect::pollEvents(SDL_Event* event) {
	if (event->type == SDL_KEYDOWN) {
		switch (event->key.keysym.sym) {
		case SDLK_LEFT:
			_x -= 10;
			break;
		case SDLK_RIGHT:
			_x += 10;
			break;
		case SDLK_UP:
			_y -= 10;
			break;
		case SDLK_DOWN:
			_y += 10;
			break;
		}
	}
}

void Rect::draw() const {
	SDL_Rect rect;

	rect.w = _w;
	rect.h = _h;
	rect.x = _x;
	rect.y = _y;

	SDL_SetRenderDrawColor(_renderer, 0xFF, 0x00, 0xFF, 0xFF);
	SDL_RenderFillRect(_renderer, &rect);
}
