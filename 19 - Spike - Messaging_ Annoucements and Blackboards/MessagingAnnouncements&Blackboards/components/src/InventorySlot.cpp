#include "../hdr/InventorySlot.h"

InventorySlot::InventorySlot(std::string item_EUID, Entity* item) {
	if (item->getTag() == EntityTag::E_ITEM) {
		_item_EUID = item_EUID;
		_item = item;
	}
}


Entity* InventorySlot::getItem() { return _item; }
InventorySlot* InventorySlot::getNext() { return _next; }

void InventorySlot::setItem(std::string item_EUID, Entity* item) {
	if (item->getTag() == EntityTag::E_ITEM) {
		_item_EUID = item_EUID;
		_item = item;
	}
}
void InventorySlot::setNext(InventorySlot* next) { _next = next; }
