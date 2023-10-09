#include "../hdr/InventorySlot.h"

InventorySlot::InventorySlot(Entity* item) {
	if (item->getTag() == EntityTag::ITEM) { _item = item; }
}
InventorySlot::~InventorySlot() {
	if (_item != nullptr) {
		delete _item;
		_item = nullptr;
	}
}

Entity* InventorySlot::getItem() { return _item; }
InventorySlot* InventorySlot::getNext() { return _next; }
void InventorySlot::setItem(Entity* item) { _item = item; }
void InventorySlot::setNext(InventorySlot* next) { _next = next; }
