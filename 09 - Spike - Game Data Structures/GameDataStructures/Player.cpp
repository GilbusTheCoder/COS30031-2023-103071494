#include <iostream>
#include "Player.h"
#include "Inventory.h"


Player::Player() {
	std::cout << "The player has entered this magical realm." << std::endl; }

void Player::takeItem(InventoryItem* item_ptr) {
	_inventory.addItem(item_ptr); }

void Player::removeItem(InventoryItem* item_ptr) {
	_inventory.deleteItem(item_ptr); }

void Player::showInventory() {
	_inventory.show(); }
