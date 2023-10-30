#include "../hdr/Rect.h"
#include <iostream>

Rect::Rect::Rect(Window* window, int w, int h, int x, int y,
	Colour colour) : _w(w), _h(h), _x(x), _y(y), _colour(colour) {
	_renderer = window->getRenderer();

	if (_renderer == nullptr) { std::cerr << "Rect not given valid renderer.\n"; }
	if (!_rect) { _rect = new SDL_Rect(); }
	_rect->w = _w;
	_rect->h = _h;
	_rect->x = _x;
	_rect->y = _y;
}


std::pair<int, int> Rect::Rect::getXY() { return { _x, _y }; }
std::pair<int, int> Rect::Rect::getDimensions() { return { _w, _h }; }
Rect::Colour Rect::Rect::getColour() { return _colour; }

void Rect::Rect::setXY(std::pair<int, int> x_y) {
	_x = std::get<0>(x_y);
	_y = std::get<1>(x_y); }

void Rect::Rect::setColor(Colour colour) {
	_colour.r = colour.r;
	_colour.g = colour.g;
	_colour.b = colour.b;
	_colour.a = colour.a;
}



// 0 for negative, 1 for positive
void Rect::Rect::update(int sign, int dx, int dy) {
	if (sign) {	_x += dx; _y += dy;	}
	else { _x -= dx; _y -= dy; }

	_rect->x = _x;
	_rect->y = _y;
}

void Rect::Rect::render() const {
	SDL_SetRenderDrawColor(_renderer, _colour.r, _colour.g, _colour.b, _colour.a);
	SDL_RenderFillRect(_renderer, _rect);
}
