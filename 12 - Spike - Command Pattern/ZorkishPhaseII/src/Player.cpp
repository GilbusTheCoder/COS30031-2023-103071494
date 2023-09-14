#include "../header/pch.h"
#include "../header/Player.h"

Player::Player(InventorySlot* _init_slot) {
	_inventory = Inventory(_init_slot);
}

void Player::takeItem(Item* item_ptr) {
	_inventory.addItem(item_ptr);
}

void Player::removeItem(Item* item_ptr) {
	_inventory.deleteItem(item_ptr);
}

void Player::showInventory() {
	_inventory.show();
}
