#include "../hdr/Rect.h"
#include <iostream>

Shape::Rect::Rect() {
	_x = 0;
	_y = 0;
	_w = 0;
	_h = 0;
	_type = ShapeType::INVALID;
}

Shape::Rect::Rect(Window* window, int w, int h, int x, int y,
	ShapeType type, ColourRGBA colour) : _w(w), _h(h) {
	_x = x; _y = y;
	_type = type;
	_colour = colour;
	findBounds();
	_renderer = window->getRenderer();

	if (_renderer == nullptr) { 
		std::cerr << "Rect entity couldn't instance renderer.\n"; }
}

void Shape::Rect::setPos(std::pair<int, int> pos) {
	auto [x, y] = pos;

	_x = x;
	_y = y;
	findBounds(); }

void Shape::Rect::render() {
	SDL_SetRenderDrawColor(_renderer, _colour.r, _colour.g, _colour.b, _colour.a);
	SDL_RenderFillRect(_renderer, _bounds); }

void Shape::Rect::findBounds() {
	if (_bounds) { delete _bounds; _bounds = nullptr; }
	
	_bounds = new SDL_Rect();
	_bounds->w = _w;
	_bounds->h = _h;
	_bounds->x = _x;
	_bounds->y = _y; }
