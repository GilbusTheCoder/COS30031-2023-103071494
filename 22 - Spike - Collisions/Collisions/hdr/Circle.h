#pragma once
#include "Window.h"
#include "Shape.h"

namespace Shape {
	class Circle : public Shape {
	private:
		SDL_Point _origin;
		int _radius;
		
	public:
		Circle(Window* window, SDL_Point origin, int radius, 
			ShapeType type, ColourRGBA colour);

		inline SDL_Point getOrigin() { return _origin; }
		inline int getRadius() { return _radius; }

		inline void setOrigin(SDL_Point new_origin) { _origin = new_origin; }
		inline void setRadius(int new_radius) { _radius = new_radius; }

		void render() override;

	private:
		void findBounds() override;
	};
}

