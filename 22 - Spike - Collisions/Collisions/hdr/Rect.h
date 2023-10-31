#pragma once
#include "Window.h"
#include "Shape.h"

/*	For now im reluctant to call this rectangle class a 2d renderer or
*	collider mesh or anything as given the trivial nature of the software
*	it's ok for the rect to do both. Therefore, in this case it does both
*	paint to renderer and handle collisions								*/

namespace Shape {
	class Rect : public Shape {
	private:		
		int _w, _h;
	
	public:
		//	Could just move that data into structs if i wanted
		Rect();
		Rect(Window* window, int w, int h, int x, int y, ShapeType type, ColourRGBA colour);

		void setPos(std::pair<int, int> pos);
		inline std::pair<int, int> getDimensions() { return {_w, _h}; }
		inline void resize(int new_w, int new_h) { _w=new_w; _h=new_h; }
		
		void render() override;

	private:
		inline void setDimensions(int w, int h, int x, int y) { _w=w; _h=h; _x=x; _y = y; }
		void findBounds() override;
	};
}

