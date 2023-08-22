#pragma once
#include "Inventory.h"

class Player {
private:
	Inventory _inventory;

public:
	Player(InventorySlot* _init_slot);
	Player();

	//Wrappers for the inventory
	InventorySlot takeItem(InventoryItem* item_ptr);
	void removeItem(InventoryItem* item_ptr);
	void showInventory();
};