#include "../hdr/Inventory.h"
/******************************************************************************
*							    De/Constructors
******************************************************************************/
Inventory::Inventory(ItemSlot* head, int max_size)
	:_head(head), _max_size(max_size) {
	if (_head != nullptr) { _size++; }
}

Inventory::~Inventory() { reset(); }


/******************************************************************************
*								  Properties
******************************************************************************/
ItemSlot* Inventory::getHead() { return _head; }

// Will return a nullptr only if the _head is null
ItemSlot* Inventory::getTail() {
	ItemSlot* traversal_ptr = _head;

	if (_head != nullptr) {
		while (traversal_ptr->getNext() != nullptr) {
			traversal_ptr = traversal_ptr->getNext();
		}
	}

	return traversal_ptr;
}

int Inventory::getSize() { return _size; }
int Inventory::getMaxSize() { return _max_size; }

void Inventory::setHead(ItemSlot* head) { _head = head; }
void Inventory::resetHead(ItemSlot* head) {
	ItemSlot* new_head = head;
	reset();
	_head = new_head;
	_size++;
}

/******************************************************************************
*								   Utility
******************************************************************************/
void Inventory::addItem(Item* item) {
	ItemSlot* new_tail = new ItemSlot(item);

	if (_head == nullptr) { _head = new_tail; }
	else {
		ItemSlot* old_tail = getTail();
		old_tail->setNext(new_tail);
	}
}

void Inventory::deleteItem(Item* item) {
	if (_head != nullptr) {
		// Check the bulk of the list
		ItemSlot* traversal_ptr = _head;
		ItemSlot* previous_slot_ptr = nullptr;

		while (traversal_ptr->getNext() != nullptr) {
			if (traversal_ptr->getItem() != item) {
				previous_slot_ptr = traversal_ptr;
				traversal_ptr = traversal_ptr->getNext();
			}
			else {
				previous_slot_ptr->setNext(traversal_ptr->getNext());
				delete traversal_ptr;
			}
		}

		// Check the tail of the list as it's excluded by the loop
		if (traversal_ptr->getItem() == item) {
			previous_slot_ptr->setNext(nullptr);
			delete traversal_ptr;
		}
	}
}

void Inventory::reset() {
	if (_head != nullptr) {
		ItemSlot* traversal_ptr = _head;
		ItemSlot* prev_ptr = nullptr;

		if (_head != nullptr) {
			while (traversal_ptr->getNext() != nullptr) {
				prev_ptr = traversal_ptr;
				traversal_ptr = traversal_ptr->getNext();

				delete prev_ptr;
			}
			_head = nullptr;
			delete traversal_ptr;
		}

		_size = 0;
	}
}

void Inventory::about() {
	if (_head != nullptr) {
		ItemSlot* traversal_ptr = _head;

		if (traversal_ptr != nullptr) {
			while (traversal_ptr->getNext() != nullptr) {
				traversal_ptr->about();
				traversal_ptr = traversal_ptr->getNext();
			}

			traversal_ptr->about();
		}
	}
}
