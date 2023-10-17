#include "../hdr/C_Inventory.h"

/******************************************************************************
*							    De/Constructors
******************************************************************************/
C_Inventory::C_Inventory(std::string ucid,
	std::vector<InventorySlot*> slots, int max_size)
	: _ucid(ucid), _max_size(max_size) {
	if (!slots.empty()) { for (auto slot : slots) { addItem(slot); } }
}

/******************************************************************************
*								  Properties
******************************************************************************/
ComponentFlag C_Inventory::getFlag() { return _flag; }
InventorySlot* C_Inventory::getHead() { return _head; }

// Will return a nullptr only if the _head is null
InventorySlot* C_Inventory::getTail() {
	InventorySlot* traversal_ptr = _head;

	if (_head != nullptr) {
		while (traversal_ptr->getNext() != nullptr) {
			traversal_ptr = traversal_ptr->getNext();
		}
	}

	return traversal_ptr;
}

int C_Inventory::getSize() { return _size; }
int C_Inventory::getMaxSize() { return _max_size; }

void C_Inventory::setHead(InventorySlot* head) { _head = head; }

/******************************************************************************
*								   Utility
******************************************************************************/
/*	Searches through itself for the item in question, will return the position
*	of the item relative to the head (0 if item isn't found					*/
int C_Inventory::hasItem(Entity* item, std::string UEID) {
	if (_head != nullptr) {
		int slot_offset = 1;
		InventorySlot* traversal_ptr = _head;

		if (item != nullptr) {
			while (traversal_ptr != nullptr) {
				if (traversal_ptr->getItem()->getID() == item->getID()) {
					return slot_offset;
				}

				if (traversal_ptr->getNext() == nullptr) { return 0; }
				else {
					traversal_ptr = traversal_ptr->getNext();
					slot_offset++;
				}
			}
		}
		else if (UEID != "") {
			while (traversal_ptr != nullptr) {
				if (traversal_ptr->getItem()->getID() == UEID) {
					return slot_offset;
				}

				if (traversal_ptr->getNext() == nullptr) { return 0; }
				else {
					traversal_ptr = traversal_ptr->getNext();
					slot_offset++;
				}
			}
		}
	}
	return 0;
}

//Only call after calling has item to ensure the item exists within the inventory
Entity* C_Inventory::getItem(int offset) {
	InventorySlot* traversal_ptr = _head;

	for (int idx = 1; idx < offset; idx++) {
		traversal_ptr = traversal_ptr->getNext();
	}

	return traversal_ptr->getItem();
}

void C_Inventory::addItem(Entity* item) {
	InventorySlot* new_tail = new InventorySlot(item->getID(), item);
	held_item_EUIDs.emplace_back(item->getID());

	if (_head == nullptr) { _head = new_tail; }
	else {
		InventorySlot* old_tail = getTail();
		old_tail->setNext(new_tail);
	}
}

void C_Inventory::addItem(InventorySlot* slot) {
	if (_head == nullptr) {
		_head = slot;

		if (_head->getItem() != nullptr) {
			held_item_EUIDs.emplace_back(_head->getItem()->getID());
		}
	}
	else {
		InventorySlot* old_tail = getTail();
		old_tail->setNext(slot);

		if (slot->getItem() != nullptr) {
			held_item_EUIDs.emplace_back(slot->getItem()->getID());
		}
	}
}

void C_Inventory::deleteItem(Entity* item) {
	int offset = hasItem(item);

	if (offset) {
		InventorySlot* prev_ptr = nullptr;
		InventorySlot* traversal_ptr = _head;

		for (int slot_idx = 1; slot_idx < offset; ++slot_idx) {
			prev_ptr = traversal_ptr;
			traversal_ptr = traversal_ptr->getNext();
		}

		if (traversal_ptr == _head) {
			if (_head->getNext() != nullptr) {
				_head = _head->getNext();
			}
		}
		else if (traversal_ptr->getNext() != nullptr) {
			prev_ptr->setNext(traversal_ptr->getNext());
		}


		std::string deleted_ID = traversal_ptr->getItem()->getID();
		for (auto id_it = held_item_EUIDs.begin();
			id_it != held_item_EUIDs.end(); ++id_it) {
			if (*id_it == deleted_ID) {
				held_item_EUIDs.erase(id_it);
				held_item_EUIDs.shrink_to_fit();
				break;
			}
		}

		delete traversal_ptr;
		traversal_ptr = nullptr;
	}
}

void C_Inventory::update() { }
void C_Inventory::render() { }