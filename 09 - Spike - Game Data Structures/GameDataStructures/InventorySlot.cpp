#include <iostream>
#include "InventorySlot.h"
#include "InventoryItem.h"

InventorySlot::InventorySlot() {
	_item = nullptr;
	_next = nullptr;
}

InventorySlot::InventorySlot(InventoryItem* item_ptr) {
	_item = item_ptr;
	_next = nullptr;
};

InventoryItem* InventorySlot::getItem() { return _item; }

InventorySlot* InventorySlot::getNext() {
	if (_next != nullptr) { return _next; }
	else { return nullptr; }
}

void InventorySlot::setItem(InventoryItem* item_ptr) { _item = item_ptr; }
void InventorySlot::setNext(InventorySlot* next_ptr) { _next = next_ptr; }

void InventorySlot::about() {
	std::cout << "data: " << _item << std::endl;
	std::cout << "next: " << _next << std::endl;
}

