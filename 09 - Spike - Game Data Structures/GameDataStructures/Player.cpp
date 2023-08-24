#include <iostream>
#include "Player.h"
#include "Inventory.h"


Player::Player() {
	InventoryItem _init_item = InventoryItem("Stick of Testing", "testType", "Default item for the player to test stuff with");
	InventorySlot _init_slot = InventorySlot(&_init_item);
	_inventory = Inventory(&_init_slot);
}

Player::Player(InventorySlot* _init_slot) {
	_inventory = Inventory(_init_slot);
}

void Player::takeItem(InventoryItem* item_ptr) {
	_inventory.addItem(item_ptr); }

void Player::removeItem(InventoryItem* item_ptr) {
	_inventory.deleteItem(item_ptr); }

void Player::showInventory() {
	_inventory.show(); }
