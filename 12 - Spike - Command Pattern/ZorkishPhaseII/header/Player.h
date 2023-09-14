#pragma once
#include "Inventory.h"

class Player {
private:
	Inventory _inventory;

public:
	Player(InventorySlot* _init_slot = nullptr);

	//Wrappers for the inventory
	void takeItem(Item* item_ptr);
	void removeItem(Item* item_ptr);
	void showInventory();
};
