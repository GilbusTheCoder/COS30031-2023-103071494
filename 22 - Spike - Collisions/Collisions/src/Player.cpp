#include "../hdr/Player.h"

Player::Player(Window* window, int w, int h, int x, int y, 
	Rect::Colour colour): _w(w), _h(h), _x(x), _y(y), _colour(colour) {
	if (!_rect) { _rect = new Rect::Rect(window, w, h, x, y, colour); } 
}

Player::~Player() { if (_rect) {delete _rect; _rect = nullptr; } }




Rect::Rect* Player::getRect() { return _rect; }
Rect::Colour Player::getColour() { return _colour; }
Rect::Colour Player::getHighlightedColour() { return _highlighted_colour; }
std::pair<int, int> Player::getXY() { return { _x, _y }; }

void Player::setXY(std::pair<int, int> x_y) {
	_x = std::get<0>(x_y);
	_y = std::get<1>(x_y);

	_rect->setXY(x_y); }




void Player::update(SDL_Event* event) {
	std::pair<int, int> input_data = handleInput(event);
	
	// Moving along the y axis?
	if (std::get<1>(input_data) == 1) {
		_rect->update(std::get<0>(input_data), 0, _velocity);
	}	// Or moving along the x? 
	else if (std::get<1>(input_data) == 0) {
		_rect->update(std::get<0>(input_data), _velocity, 0); } 
}

void Player::render() {
	_rect->render(); }




// First integer is sign (0 = -, 1 = +) second is for axis (0 = x, 1 = y)
std::pair<int, int> Player::handleInput(SDL_Event* event) {
	int sign = -1, axis = -1;
	if (event->type == SDL_KEYDOWN) {
		switch (event->key.keysym.sym) {
		case SDLK_LEFT:
			_x -= _velocity;
			sign = 0; axis = 0;
			break;
		case SDLK_RIGHT:
			_x += _velocity;
			sign = 1; axis = 0;
			break;
		case SDLK_UP:
			_y -= _velocity;
			sign = 0; axis = 1;
			break;
		case SDLK_DOWN:
			_y += _velocity;
			sign = 1; axis = 1;
			break;
		}
	}

	return { sign, axis };
}
