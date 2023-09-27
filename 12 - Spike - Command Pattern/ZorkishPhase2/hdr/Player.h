#pragma once
#include "Inventory.h"

class Player {
private:
	Inventory* _inventory;

public:
	Player();
	~Player();

	// Inventory wrappers
	void takeItem(Item* item);
	void deleteItem(Item* item);
	bool hasItem(std::string item_name);
	Item* findItem(std::string item_name);
	void showInventory();
};
