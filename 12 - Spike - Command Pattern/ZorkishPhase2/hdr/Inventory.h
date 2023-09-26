#pragma once
#include "ItemSlot.h"

class Inventory {
private:
	ItemSlot* _head = nullptr;
	int _size = 0;
	int _max_size;

public:
	Inventory(ItemSlot* head = nullptr, int max_size = 64);
	~Inventory();

	ItemSlot* getHead();
	ItemSlot* getTail();
	int getSize();
	int getMaxSize();
	void setHead(ItemSlot* head);
	void resetHead(ItemSlot* head);

	void addItem(Item* item);
	void deleteItem(Item* item);
	void reset();
	void about();
};

