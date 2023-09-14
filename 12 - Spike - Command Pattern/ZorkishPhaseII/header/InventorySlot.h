#pragma once
#include "Items.h"

class InventorySlot {
private:
	Item* _item;
	InventorySlot* _next;

public:
	InventorySlot(Item* item_ptr = nullptr);

	Item* getItem();
	void setItem(Item* item_ptr);
	InventorySlot* getNext();
	void setNext(InventorySlot* next);

	void about();
};

