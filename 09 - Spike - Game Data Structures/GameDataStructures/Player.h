#pragma once
#include "Inventory.h"

class Player {
private:
	Inventory _inventory;

public:
	Player(InventorySlot* _init_slot);
	Player();


	void takeItem(InventoryItem* item_ptr);		//Wrappers for the inventory
	void removeItem(InventoryItem* item_ptr);
	void showInventory();
};