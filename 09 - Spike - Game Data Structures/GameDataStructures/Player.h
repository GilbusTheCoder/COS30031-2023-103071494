#pragma once
#include "Inventory.h"

class Player {
private:
	InventoryItem _init_item = InventoryItem("Stick of Testing", "testType", "Default item for the player to test stuff with");
	InventorySlot _init_slot = InventorySlot(&_init_item);
	Inventory _inventory = Inventory(&_init_slot);

public:
	Player() {};

	void takeItem(InventoryItem* item_ptr) {};		//Wrappers for the inventory
	void removeItem(InventoryItem* item_ptr) {};
	void showInventory() {};
};