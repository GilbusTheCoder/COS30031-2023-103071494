#include <iostream>
#include "InventorySlot.h"
#include "InventoryItem.h"

InventorySlot::InventorySlot(InventoryItem* item_ptr) {
	_item = item_ptr;
	_next = nullptr;
};

InventoryItem* InventorySlot::getItem() { return _item; }
InventorySlot* InventorySlot::getNext() {
	if (_next != nullptr) { return _next; }
	else {
		InventorySlot* hack_fix = nullptr;
		return hack_fix;
	}
}

void InventorySlot::setItem(InventoryItem* item_ptr) { _item = item_ptr; }
void InventorySlot::setNext(InventorySlot* next_ptr) { _next = next_ptr; }

void InventorySlot::about() {
	std::cout << "data: " << _item << std::endl;
	std::cout << "next: " << _next << std::endl;
}

