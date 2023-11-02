#include <iostream>
#include <algorithm>
#include "../hdr/Circle.h"

Shape::Circle::Circle(Window* window, SDL_Point origin, int radius,
	ShapeType type, ColourRGBA colour) : _origin(origin), _radius(radius) {
	_type = type;
	_colour = colour;
	findBounds();
	_renderer = window->getRenderer();

	if (_renderer == nullptr) {
		std::cerr << "Circle entity couldn't instance renderer.\n"; }	
}


void Shape::Circle::setPos(std::pair<int, int> pos) {
	auto [x, y] = pos;
	float half_rad = _radius / 2;

	SDL_Point new_origin;
	new_origin.x = x + half_rad;
	new_origin.y = y + half_rad;

	setOrigin(new_origin);
	findBounds();
}

void Shape::Circle::render() {
	if (_renderer) {
		int renderer_width, renderer_height;	// Clamp values
		SDL_GetRendererOutputSize(_renderer, &renderer_width, &renderer_height);
		SDL_SetRenderDrawColor(_renderer, _colour.r, _colour.g, _colour.b, _colour.a);

		int x0 = _origin.x;						// x origin 
		int y0 = _origin.y; 					// y origin
		int x1 = _bounds->x;						// x initial
		int x2 = _bounds->x + _bounds->w;			// x final
		int y1 = _bounds->y; 					// y initial
		int y2 = _bounds->y + _bounds->h;			// y final
		
		x1 = std::clamp(x1, 0, renderer_width);
		x2 = std::clamp(x2, 0, renderer_width);
		y1 = std::clamp(y1, 0, renderer_width);
		y2 = std::clamp(y2, 0, renderer_width);
		
		for (int x = x1; x < x2; ++x) {
			for (int y = y1; y < y2; ++y) {
				// If >= 0 we have a renderable pixel (filled circles if outline check == 0)
				int render_value = (x-x0)*(x-x0) + (y-y0)*(y-y0) - _radius*_radius;
				if (render_value <= 0) { SDL_RenderDrawPoint(_renderer, x, y); }
			}
		}
	}
}

void Shape::Circle::findBounds() { 
	int x1 = _origin.x - _radius;
	int y1 = _origin.y - _radius;
	int diameter = 2 * _radius;

	if (_bounds) { delete _bounds; _bounds = nullptr; }
	_bounds = new SDL_Rect();

	_bounds->w = diameter;
	_bounds->h = diameter;
	_bounds->x = x1;
	_bounds->y = y1;
}
