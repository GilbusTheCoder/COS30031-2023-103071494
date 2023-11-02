#pragma once
#include "Rect.h"
#include "Circle.h"

class Player {
private:
	// Cleanup handled by the GameWorld
	Shape::Shape* _collider = nullptr;
	Shape::ColourRGBA _colour_a, _colour_b;

	int _x, _y;
	int _velocity = 5;
	
public:
	bool displaying_highlighted = false;

public:
	Player(Window* window, int w, int h, int x, int y, Shape::ColourRGBA colour, 
		Shape::ColourRGBA collision_colour, Shape::Shape* collider = nullptr);

	void setPos(std::pair<int, int> pos);

	inline std::pair<int, int> getPos() { return {_x, _y}; }
	inline Shape::Shape* getCollider() { return _collider; }
	inline Shape::ColourRGBA getColour() { return _colour_a; }
	inline Shape::ColourRGBA getHighlightedColour() { return _colour_b; } 

	void update(std::pair<int, int> move_data);
	void render();
};