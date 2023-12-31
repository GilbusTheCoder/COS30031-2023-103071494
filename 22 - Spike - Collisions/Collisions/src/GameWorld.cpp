#include <iostream>
#include "../hdr/GameWorld.h"

GameWorld::GameWorld(Window* window) {
	_window = window;
	
	if (_window) {
		Shape::ColourRGBA test_colour;
		Shape::ColourRGBA player_colour;
		player_colour.b = 0;
		player_colour.r = 150;
		
		Shape::ColourRGBA highlight_colour;
		highlight_colour.g = 120;
		highlight_colour.r = 0;

		SDL_Point origin_1;
		origin_1.x = 400;
		origin_1.y = 250;


		SDL_Point origin_2;
		origin_2.x = 100;
		origin_2.y = 250;

		_renderer = _window->getRenderer();
		Shape::Shape* player_rect = new Shape::Rect(_window, 120, 120, 100, 100,
			Shape::ShapeType::RECT, player_colour);
		Shape::Shape* player_circle = new Shape::Circle(_window, origin_2, 40,
			Shape::ShapeType::CIRCLE, player_colour);
		Shape::Shape* rect_test = new Shape::Rect(_window, 50, 300, 600, 50, 
			Shape::ShapeType::RECT, test_colour);
		Shape::Shape* circle_test = new Shape::Circle(_window, origin_1, 20, 
			Shape::ShapeType::CIRCLE, test_colour);
		

		bool is_player_rect = false;
		if (is_player_rect) {
			_player = new Player(window, 120, 120, 120, 100, player_colour,
				highlight_colour, player_rect);
			addShape(player_rect);
		}
		else {
			_player = new Player(window, 120, 120, origin_2.x - 20, origin_2.y - 20, player_colour,
				highlight_colour, player_circle);
			addShape(player_circle);
		}
	
		addShape(rect_test);
		addShape(circle_test);
				
	}
}

GameWorld::~GameWorld() {
	if (_player) { delete _player; _player = nullptr; }
	for (auto shape : _shapes) { delete shape; shape = nullptr; }
}

void GameWorld::update(SDL_Event* event) {
	std::pair<int, int> init_player_pos = _player->getPos();
	
	std::pair<int, int> move_data = handleInput(event);
	_player->update(move_data); 

	std::vector<Shape::Shape*>::iterator shapes_it = _shapes.begin() + 1;
	for (shapes_it; shapes_it != _shapes.end(); ++shapes_it) {
		if (checkCollision(_player->getCollider(), *shapes_it)) {
			handleCollisions(init_player_pos);
		}
	}
}

void GameWorld::render() {
	_player->render();
	
	if (_shapes.size() > 1) {
		std::vector<Shape::Shape*>::iterator shapes_it = _shapes.begin() + 1;
		
		for (shapes_it; shapes_it != _shapes.end(); ++shapes_it) {
			(*shapes_it)->render(); }
	}
}


// first int for axis (0 for x, 1 for y) second for direction (0 for -, 1 for +).
std::pair<int, int> GameWorld::handleInput(SDL_Event* event) {
	if (event->type == SDL_KEYDOWN) {
		std::pair<int, int> input_data;

		switch (event->key.keysym.sym) {
		case SDLK_LEFT:
			input_data = { 0, 0 };
			break;
		case SDLK_RIGHT:
			input_data = { 0, 1 };
			break;
		case SDLK_UP:
			input_data = { 1, 0 };
			break;
		case SDLK_DOWN:
			input_data = { 1, 1 };
			break;
		default:
			input_data = { -1, -1 };
			break;
		}

		return input_data;
	}
}

bool GameWorld::checkCollision(Shape::Shape* shape1, Shape::Shape* shape2) {
	auto shape_type_1 = shape1->getType();
	auto shape_type_2 = shape2->getType();
	
	switch (shape_type_1) {
	case Shape::ShapeType::RECT:
		switch (shape_type_2) {
		case Shape::ShapeType::RECT:
			return checkRectCollision((Shape::Rect*)shape1, (Shape::Rect*)shape2);
		case::Shape::ShapeType::CIRCLE:
			return false;
		default: return false;
		}		//	Not implemented

	case Shape::ShapeType::CIRCLE: {
		switch (shape_type_2) {
		case Shape::ShapeType::RECT:
			return false;
		case Shape::ShapeType::CIRCLE:
			return checkCircleCollision((Shape::Circle*)shape1, (Shape::Circle*)shape2);
		default: return false; }
		} default: return false; 
	}

	return false;
}

bool GameWorld::checkRectCollision(Shape::Rect* rect1, Shape::Rect* rect2) {
	auto[x1, y1] = rect1->getPos();
	auto[x2, y2] = rect2->getPos();
	auto[w1, h1] = rect1->getDimensions();
	auto[w2, h2] = rect2->getDimensions();
	

	if ( x1 < x2 + w2 &&
		 x1 + w1 > x2 &&
		 y1 < y2 + h2 &&
		 y1 + h1 > y2) { 
		return true; }
	
	return false;
}

bool GameWorld::checkCircleCollision(Shape::Circle* circle1, Shape::Circle* circle2) {
	int r1 = circle1->getRadius();
	int r2 = circle2->getRadius();
	int total_r_squared = (r1 + r2) * (r1 + r2);
	double dist_squared = distanceSquared(circle1->getOrigin(), circle2->getOrigin());

	return dist_squared < total_r_squared ; }

void GameWorld::handleCollisions(std::pair<int, int> prev_entity_pos) {
	_player->displaying_highlighted = !_player->displaying_highlighted;
	_player->setPos(prev_entity_pos); }

double GameWorld::distanceSquared(SDL_Point p1, SDL_Point p2) {
	double dx = p2.x - p1.x;
	double dy = p2.y - p1.y;
	
	return dx*dx + dy*dy; }
