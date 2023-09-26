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
};
