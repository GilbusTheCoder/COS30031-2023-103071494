#pragma once
#include "Window.h"

/*	For now im reluctant to call this rectangle class a 2d renderer or
*	collider mesh or anything as given the trivial nature of the software
*	it's ok for the rect to do both. Therefore, in this case it does both
*	render and handle collisions										*/

namespace Rect {
	struct Colour {
		int r, g, b, a; };

	class Rect {
	private:		
		SDL_Renderer* _renderer = nullptr;
		SDL_Rect* _rect = nullptr;

		int _w, _h;
		int _x, _y;
		Colour _colour;
	
	public:
		//	Could just move that data into structs if i wanted
		Rect(Window* window, int w, int h, int x, int y, Colour colour);

		std::pair<int, int> getXY();
		std::pair<int, int> getDimensions();
		Colour getColour();

		void setXY(std::pair<int, int> x_y);
		void setColor(Colour colour);

		void update(int sign, int dx, int dy);
		void render() const;	
	};
}

