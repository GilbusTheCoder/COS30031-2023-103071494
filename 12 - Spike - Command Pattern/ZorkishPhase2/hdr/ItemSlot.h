#pragma once
#include "Item.h"

class ItemSlot {
private:
	Item* _item = nullptr;
	ItemSlot* _next = nullptr;

public:
	ItemSlot(Item* item = nullptr);
	~ItemSlot();

	Item* getItem();
	ItemSlot* getNext();
	void setItem(Item* item);
	void setNext(ItemSlot* next);

	void about();
};

