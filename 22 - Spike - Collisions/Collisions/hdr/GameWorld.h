#pragma once
#include <vector>
#include "Player.h"

class GameWorld {
private:
	Window* _window = nullptr;
	SDL_Renderer* _renderer = nullptr;

	Player* _player = nullptr;

	std::vector<Rect::Rect*> _rects;

public:
	GameWorld(Window* window);
	~GameWorld();

	void update(SDL_Event* event);
	void render();

private:

	bool checkCollision(Rect::Rect* rect1, Rect::Rect* rect2);
	void addRect(Rect::Rect* rect);
};


