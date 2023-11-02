#pragma once
#include <vector>
#include "Window.h"
#include "Player.h"

class GameWorld {
private:
	SDL_Renderer* _renderer = nullptr;
	Window* _window = nullptr;

	std::vector<Shape::Shape*> _shapes;
	Player* _player = nullptr;

public:
	GameWorld(Window* window);
	~GameWorld();

	void update(SDL_Event* event);
	void render();

private:
	inline void addShape(Shape::Shape* shape) { _shapes.emplace_back(shape); }
	std::pair<int, int> handleInput(SDL_Event* event);

	bool checkCollision(Shape::Shape* shape1, Shape::Shape* shape2);
	bool checkRectCollision(Shape::Rect* rect1, Shape::Rect* rect2);
	bool checkCircleCollision(Shape::Circle* circle1, Shape::Circle* circle2);


	void handleCollisions(std::pair<int, int> prev_entity_pos);
	double distanceSquared(SDL_Point p1, SDL_Point p2);
};


