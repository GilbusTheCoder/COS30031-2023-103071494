#include <iostream>
#include "Inventory.h"
#include "InventorySlot.h"

Inventory::Inventory(InventorySlot* head) {
	_head = head;
	_size++;
}

InventorySlot* Inventory::getHead() { return _head; }
InventorySlot* Inventory::getTail() {
	InventorySlot* traversal_ptr = _head;

	while (traversal_ptr->getNext() != nullptr) {
		traversal_ptr = traversal_ptr->getNext();
	}
	return traversal_ptr;
}


InventorySlot Inventory::addItem(InventoryItem* item_ptr) {
	InventorySlot new_item = InventorySlot(item_ptr);
	InventorySlot* tail = getTail();

	tail->setNext(&new_item);
	_size++;

	return new_item;
}


void Inventory::deleteItem(InventoryItem* item_ptr) {
	InventorySlot* previous_ptr = nullptr;
	InventorySlot* traversal_ptr = _head;

	while (traversal_ptr->getItem() != item_ptr) {
		previous_ptr = traversal_ptr;
		traversal_ptr = traversal_ptr->getNext();
	}

	previous_ptr->setNext(traversal_ptr->getNext());
	traversal_ptr->setNext(nullptr);
	_size--;
}

void Inventory::show() {
	InventorySlot* traversal_ptr = _head;

	while (traversal_ptr != nullptr) {
		traversal_ptr->getItem()->printDescription();
		std::cout << std::endl;
		traversal_ptr = traversal_ptr->getNext();
	}
}