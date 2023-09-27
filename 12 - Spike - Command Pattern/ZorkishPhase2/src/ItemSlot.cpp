#include "../hdr/ItemSlot.h"

ItemSlot::ItemSlot(Item* item) :_item(item) {}
ItemSlot::~ItemSlot() {
	if (_item != nullptr) {
		delete _item;
		_item = nullptr;
	} 
}

Item* ItemSlot::getItem() { return _item; }
ItemSlot* ItemSlot::getNext() { return _next; }
void ItemSlot::setItem(Item* item) { _item = item; }
void ItemSlot::setNext(ItemSlot* next) { _next = next; }

void ItemSlot::about() {
	if (_item != nullptr) {
		std::cout << "Item data: " << std::endl;
		_item->about();
	} else { std::cout << "No item" << std::endl; }
}