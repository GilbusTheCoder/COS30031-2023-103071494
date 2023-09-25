#include "../hdr/Player.h"

Player::Player() :_inventory(new Inventory()) {};
Player::~Player() {
	if (_inventory != nullptr) { 
		delete _inventory; 
		_inventory = nullptr;
	}
}

/*	Need to create a deep copy of the item so that we can delete it from the 
*	current location. This will be handled by the Gameplay State. */			
void Player::takeItem(Item* item) {
	_inventory->addItem(item);
}

/*	The item passed to the function will already exist in the inventory.
*	Therefore no checks really need to be written							*/
void Player::deleteItem(Item* item) {
	_inventory->deleteItem(item);
}
