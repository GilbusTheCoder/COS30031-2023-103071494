#include <iostream>
#include <algorithm>
#include "../hdr/Circle.h"

Shape::Circle::Circle(Window* window, SDL_Point origin, int radius,
	ShapeType type, ColourRGBA colour) : _origin(origin), _radius(radius) {
	_type = type;
	_colour = colour;
	_renderer = window->getRenderer();
	_bounds = findBounds();

	if (_renderer == nullptr) {
		std::cerr << "Circle entity couldn't instance renderer.\n"; }	
}

void Shape::Circle::render() {
	if (_renderer) {
		int renderer_width, renderer_height;	// Clamp values
		SDL_GetRendererOutputSize(_renderer, &renderer_width, &renderer_height);
		SDL_SetRenderDrawColor(_renderer, _colour.r, _colour.g, _colour.b, _colour.a);

		int x0 = _origin.x;						// x origin 
		int y0 = _origin.y; 					// y origin
		int x1 = _bounds.x;						// x initial
		int x2 = _bounds.x + _bounds.w;			// x final
		int y1 = _bounds.y; 					// y initial
		int y2 = _bounds.y + _bounds.h;			// y final
		
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

SDL_Rect Shape::Circle::findBounds() { 
	int x1 = _origin.x - _radius;
	int y1 = _origin.y - _radius;
	int diameter = 2 * _radius;

	SDL_Rect bounds;
	bounds.w = diameter;
	bounds.h = diameter;
	bounds.x = x1;
	bounds.y = y1;

	return bounds;
}
