#include "../hdr/Inventory.h"
/******************************************************************************
*							    De/Constructors
******************************************************************************/
Inventory::Inventory(ItemSlot* head, int max_size)
	:_head(head), _max_size(max_size) {
	if (_head != nullptr) { _size++; }
	else {
		Item* init_item = new Item("lighter", "Spark spark.. good good");
		_head = new ItemSlot(init_item);
	}
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
		if (hasItem(item->getName())) {

			// Head is the only element
			if (_head == getTail() && _head->getItem() == item) { 
				delete _head; 
				_head = nullptr; 
			}
			// Bulk of the list... iterate and search
			else {
				// if head contains item and there's multiple elements
				if (_head->getItem() == item) {
					ItemSlot* old_head = _head;
					_head = old_head->getNext();

					delete old_head;
					old_head = nullptr;
				}

				ItemSlot* traversal_ptr = _head;
				ItemSlot* prev_slot = nullptr;

				while (traversal_ptr->getNext() != nullptr) {
					if (traversal_ptr->getItem() == item) {
						prev_slot->setNext(traversal_ptr->getNext());
						delete traversal_ptr;
						return;
					} else { // Increment
						prev_slot = traversal_ptr;
						traversal_ptr = traversal_ptr->getNext();
					}
				}

				// Tail of the list
				if (traversal_ptr->getItem() == item) {
					prev_slot->setNext(traversal_ptr->getNext());
					delete traversal_ptr;
				}
			}
		}
	}
}

bool Inventory::hasItem(std::string item_name) {
	if (_head != nullptr) {
		ItemSlot* traversal_ptr = _head;

		while (traversal_ptr->getNext() != nullptr) {
			if (traversal_ptr->getItem()->getName() == item_name) {
				return true;
			}

			traversal_ptr = traversal_ptr->getNext();
		}
		if (traversal_ptr->getItem()->getName() == item_name) {
			return true;
		}
	}

	return false;
}

Item* Inventory::searchItem(std::string item_name) {
	if (_head != nullptr) {
		ItemSlot* traversal_ptr = _head;
		
		while (traversal_ptr->getNext() != nullptr) {
			if (traversal_ptr->getItem()->getName() == item_name) {
				return traversal_ptr->getItem();
			}

			traversal_ptr = traversal_ptr->getNext();
		}

		if (traversal_ptr->getItem()->getName() == item_name) {
			return traversal_ptr->getItem();
		}
	}

	return nullptr;
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
				prev_ptr = nullptr;
			}

			_head = nullptr;
			delete traversal_ptr;
			traversal_ptr = nullptr;
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
