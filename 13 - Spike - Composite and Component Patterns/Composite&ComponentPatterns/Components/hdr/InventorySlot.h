#include "../../Zorkish/hdr/Entity.h"
#pragma once

class InventorySlot {
private:
	Entity* _item = nullptr;
	InventorySlot* _next = nullptr;

public:
	InventorySlot(Entity* item = nullptr);
	~InventorySlot();

	Entity* getItem();
	InventorySlot* getNext();
	void setItem(Entity* item);
	void setNext(InventorySlot* next);
};
