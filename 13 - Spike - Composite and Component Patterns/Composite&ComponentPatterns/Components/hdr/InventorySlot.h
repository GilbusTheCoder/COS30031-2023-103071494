#include "../../Zorkish/hdr/Entity.h"
#pragma once

class InventorySlot {
private:
	std::string _item_EUID;
	Entity* _item = nullptr;
	InventorySlot* _next = nullptr;

public:
	InventorySlot(std::string item_EUID, Entity* item = nullptr);

	Entity* getItem();
	InventorySlot* getNext();
	void setItem(std::string item_EUID, Entity* item);
	void setNext(InventorySlot* next);
};
