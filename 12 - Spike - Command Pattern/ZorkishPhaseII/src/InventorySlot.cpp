#include "../header/pch.h"
#include "../header/InventorySlot.h"

InventorySlot::InventorySlot(Item* item_ptr) {
	_item = item_ptr;
	_next = nullptr;
};

Item* InventorySlot::getItem() { return _item; }

InventorySlot* InventorySlot::getNext() {
	if (_next != nullptr) { return _next; }
	else { return nullptr; }
}

void InventorySlot::setItem(Item* item_ptr) { _item = item_ptr; }
void InventorySlot::setNext(InventorySlot* next_ptr) { _next = next_ptr; }

void InventorySlot::about() {
	std::cout << "data: "; _item->printDescription();
	std::cout << "next: " << _next << std::endl;
}

