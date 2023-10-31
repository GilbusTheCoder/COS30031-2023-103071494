#include "../hdr/Rect.h"
#include <iostream>

Shape::Rect::Rect(Window* window, int w, int h, int x, int y,
	ShapeType type, ColourRGBA colour) : _w(w), _h(h) {
	_x = x; _y = y;
	_type = type;
	_colour = colour;
	_bounds = findBounds();
	_renderer = window->getRenderer();

	if (_renderer == nullptr) { 
		std::cerr << "Rect entity couldn't instance renderer.\n"; }
}


void Shape::Rect::render() {
	SDL_SetRenderDrawColor(_renderer, _colour.r, _colour.g, _colour.b, _colour.a);
	SDL_RenderFillRect(_renderer, &_bounds);
}

SDL_Rect Shape::Rect::findBounds() {
	SDL_Rect bounds{
		bounds.w = _w,
		bounds.h = _h,
		bounds.x = _x,
		bounds.y = _y,
	};

	return bounds;
}
