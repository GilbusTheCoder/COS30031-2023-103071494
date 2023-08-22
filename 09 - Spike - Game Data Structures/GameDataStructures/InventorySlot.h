#pragma once
#include "InventoryItem.h"

class InventorySlot {
private:
	InventoryItem* _item;
	InventorySlot* _next;

public:
	InventorySlot(InventoryItem* item_ptr);
	
	InventoryItem* getItem();
	void setItem(InventoryItem* item_ptr);
	InventorySlot* getNext();
	void setNext(InventorySlot* next);

	void about();
};

