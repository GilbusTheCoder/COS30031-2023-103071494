#include "../hdr/Player.h"

Player::Player(Window* window, int w, int h, int x, int y, 
	Shape::ColourRGBA colour, Shape::ColourRGBA collision_colour, 
	Shape::Rect* rect) : 
	_x(x), _y(y), _colour_a(colour), _colour_b(collision_colour) {
	
	if (_rect == nullptr) {
		_rect = new Shape::Rect(window, w, h, x, y, Shape::ShapeType::RECT, colour); }	
	else { 
		_rect = rect; 
		_colour_a = _rect->getColour(); }
}

void Player::setPos(std::pair<int, int> pos) {
	auto[x, y] = pos;
	_x = x;
	_y = y;

	_rect->setPos({_x, _y});
}


void Player::update(std::pair<int, int> move_data) {
	auto [axis, direction] = move_data;

	if (!axis) {	// Horizontal movement
		if (!direction) {	// move left
			setPos({_x - _velocity, _y}); }
		else if (direction == 1){ setPos({_x + _velocity, _y}); }
	} else {	// Vertical movement
		if (!direction) {	// move up
			setPos({_x, _y - _velocity});
		} else if (direction == 1) { setPos({_x, _y + _velocity}); }
	}

	if (displaying_highlighted) {
		_rect->setColour(_colour_b); } 
	else { _rect->setColour(_colour_a); }
}

void Player::render() {
	if (_rect) _rect->render(); }

