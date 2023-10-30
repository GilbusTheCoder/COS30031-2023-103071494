#pragma once
#include "Window.h"

class Rect {
private:
	SDL_Renderer* _renderer = nullptr;

	int _w, _h;
	int _x, _y;
	int _r, _g, _b, _a;

public:
	//	Could just move that data into structs if i wanted
	Rect(Window* window, int w, int h, int x, int y, int r, int g, int b, int a);

	void pollEvents(SDL_Event* event);
	void draw() const;

private:

};

