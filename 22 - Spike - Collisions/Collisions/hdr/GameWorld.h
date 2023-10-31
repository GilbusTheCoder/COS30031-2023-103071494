#pragma once
#include <vector>
#include "Window.h"
#include "Rect.h"
#include "Circle.h"

class GameWorld {
private:
	Window* _window = nullptr;
	SDL_Renderer* _renderer = nullptr;

	//Player* _player = nullptr;

	std::vector<Shape::Shape*> _shapes;

public:
	GameWorld(Window* window);
	~GameWorld();

	//void update(SDL_Event* event);
	void render();

private:
	inline void addShape(Shape::Shape* shape) { _shapes.emplace_back(shape); }
	bool checkRectCollision(Shape::Rect* rect1, Shape::Rect* rect2);
};


