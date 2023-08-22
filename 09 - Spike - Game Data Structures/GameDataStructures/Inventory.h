#pragma once
#include "Inventory.h"
#include "InventorySlot.h"
#include "InventoryItem.h"

class Inventory {
private:
	InventorySlot* _head;	
	int _size = 0;
	int _max_size = 64;

public:
	Inventory(InventorySlot* head);

	InventorySlot* getHead();
	InventorySlot* getTail();

	InventorySlot addItem(InventoryItem* item_ptr);
	void deleteItem(InventoryItem* item_ptr);
	void show();
};

