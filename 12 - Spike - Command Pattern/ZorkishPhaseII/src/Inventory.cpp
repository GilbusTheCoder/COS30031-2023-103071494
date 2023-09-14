#include "../header/pch.h"
#include "../header/Inventory.h"

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


void Inventory::addItem(Item* item_ptr) {
	InventorySlot* new_item = new InventorySlot(item_ptr);
	InventorySlot* tail = getTail();

	tail->setNext(new_item);
	_size++;
}


void Inventory::deleteItem(Item* item_ptr) {
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
	std::cout << "Zork(ish) :: Your Inventory " << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;
	std::cout << std::endl;

	InventorySlot* traversal_ptr = _head;
	while (traversal_ptr != nullptr) {
		traversal_ptr->getItem()->printDescription();
		std::cout << std::endl;
		traversal_ptr = traversal_ptr->getNext();
	}
}