#include <iostream>
#include "../hdr/GameWorld.h"

GameWorld::GameWorld(Window* window) {
	_window = window;
	
	if (_window) {
		Shape::ColourRGBA test_colour;
		SDL_Point c_origin;
		c_origin.x = 400;
		c_origin.y = 250;

		_renderer = _window->getRenderer();
		Shape::Shape* rect_test = new Shape::Rect(_window, 120, 120, 100, 100, 
			Shape::ShapeType::RECT, test_colour);

		test_colour.b = 0;
		test_colour.r = 150;

		Shape::Shape* circle_test = new Shape::Circle(_window, c_origin, 20, 
			Shape::ShapeType::CIRCLE, test_colour);
		addShape(rect_test);
		addShape(circle_test);
		//_player = new Player(window, 120, 120, 100, 200, colour);
		//
		//// Make sure the players collider is the first to be added
		//addRect(_player->getRect()); 
		//
		//colour.b = 0;
		//Rect::Rect* wall = new Rect::Rect(window, 60, 180, 700, 100, colour);
		//addRect(wall);
	
		
	}
}

GameWorld::~GameWorld() {
	//if (_player) { delete _player; _player = nullptr; }
	for (auto shape : _shapes) { delete shape; shape = nullptr; }
}



//void GameWorld::update(SDL_Event* event) {
//	std::pair<int, int> prev_x_y = _player->getXY();
//
//	_player->update(event);
//
//	// Collision checking stuff
//	if (_rects.size() > 1) {
//		bool old_state = _player->displaying_highlighted;
//
//		std::vector<Rect::Rect*>::iterator rects_it = _rects.begin() + 1;
//		for (rects_it; rects_it != _rects.end(); ++rects_it) {
//			if (checkRectCollision(_rects[0], *rects_it)) {
//				_player->displaying_highlighted = !_player->displaying_highlighted;
//				std::cout << "Collision!\n";
//				_player->setXY(prev_x_y); }
//		
//			if (_player->displaying_highlighted) {
//				_player->getRect()->setColor(_player->getHighlightedColour());
//			} else { _player->getRect()->setColor(_player->getColour()); }
//		}
//	}
//}

void GameWorld::render() { 
	//_player->render();
	
	if (!_shapes.empty()) {
		//std::vector<Shape::Shape*>::iterator shapes_it = _shapes.begin() + 1;
		//
		//for (shapes_it; shapes_it != _shapes.end(); ++shapes_it) {
		//	(*shapes_it)->render(); }
	
		for (Shape::Shape* shape : _shapes) {
			shape->render(); }
	}
}



//bool GameWorld::checkRectCollision(Rect::Rect* rect1, Rect::Rect* rect2) {
//	int x1 = std::get<0>(rect1->getXY());
//	int x2 = std::get<0>(rect2->getXY());
//	int y1 = std::get<1>(rect1->getXY());
//	int y2 = std::get<1>(rect2->getXY());
//
//	int w1 = std::get<0>(rect1->getDimensions());
//	int w2 = std::get<0>(rect2->getDimensions());
//	int h1 = std::get<1>(rect1->getDimensions());
//	int h2 = std::get<1>(rect1->getDimensions());
//
//	if ( x1 < x2 + w2 &&
//		 x1 + w1 > x2 &&
//		 y1 < y2 + h2 &&
//		 y1 + h1 > y2) {	return true; }
//	
//	return false;
//}