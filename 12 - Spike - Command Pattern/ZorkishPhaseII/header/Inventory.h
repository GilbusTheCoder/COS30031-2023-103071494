#pragma once
#include "InventorySlot.h"

class Inventory {
private:
	InventorySlot* _head = nullptr;
	int _size = 0;
	int _max_size = 64;

public:
	Inventory(InventorySlot* head = nullptr);

	InventorySlot* getHead();
	InventorySlot* getTail();

	void addItem(Item* item_ptr);
	void deleteItem(Item* item_ptr);
	void show();
};


