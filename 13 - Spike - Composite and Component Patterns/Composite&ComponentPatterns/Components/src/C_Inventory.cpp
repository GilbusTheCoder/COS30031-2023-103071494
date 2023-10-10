#include "../hdr/C_Inventory.h"

/******************************************************************************
*							    De/Constructors
******************************************************************************/
C_Inventory::C_Inventory(int owning_entity_id, std::vector<InventorySlot*> slots, int max_size)
	:_entity_id(owning_entity_id), _max_size(max_size) { 
	if (!slots.empty()) { for (auto slot : slots) { addItem(slot); }}
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
void C_Inventory::addItem(Entity* item) {
	InventorySlot* new_tail = new InventorySlot(item);

	if (_head == nullptr) { _head = new_tail; }
	else {
		InventorySlot* old_tail = getTail();
		old_tail->setNext(new_tail);
	}
}

void C_Inventory::addItem(InventorySlot* slot) {
	if (_head == nullptr) { _head = slot; }
	else {
		InventorySlot* old_tail = getTail();
		old_tail->setNext(slot);
	}
}

//void C_Inventory::deleteItem(Entity* item) {
//	if (_head != nullptr) {
//		if (hasItem(item->getName())) {
//
//			// Head is the only element
//			if (_head == getTail() && _head->getItem() == item) {
//				delete _head;
//				_head = nullptr;
//			}
//			// Bulk of the list... iterate and search
//			else {
//				// if head contains item and there's multiple elements
//				if (_head->getItem() == item) {
//					ItemSlot* old_head = _head;
//					_head = old_head->getNext();
//
//					delete old_head;
//					old_head = nullptr;
//				}
//
//				ItemSlot* traversal_ptr = _head;
//				ItemSlot* prev_slot = nullptr;
//
//				while (traversal_ptr->getNext() != nullptr) {
//					if (traversal_ptr->getItem() == item) {
//						prev_slot->setNext(traversal_ptr->getNext());
//						delete traversal_ptr;
//						return;
//					}
//					else { // Increment
//						prev_slot = traversal_ptr;
//						traversal_ptr = traversal_ptr->getNext();
//					}
//				}
//
//				// Tail of the list
//				if (traversal_ptr->getItem() == item) {
//					prev_slot->setNext(traversal_ptr->getNext());
//					delete traversal_ptr;
//				}
//			}
//		}
//	}
//}

//bool C_Inventory::hasItem(std::string item_name) {
//	if (_head != nullptr) {
//		ItemSlot* traversal_ptr = _head;
//
//		while (traversal_ptr->getNext() != nullptr) {
//			if (traversal_ptr->getItem()->getName() == item_name) {
//				return true;
//			}
//
//			traversal_ptr = traversal_ptr->getNext();
//		}
//		if (traversal_ptr->getItem()->getName() == item_name) {
//			return true;
//		}
//	}
//
//	return false;
//}

//Entity* C_Inventory::searchItem(std::string item_name) {
//	if (_head != nullptr) {
//		ItemSlot* traversal_ptr = _head;
//
//		while (traversal_ptr->getNext() != nullptr) {
//			if (traversal_ptr->getItem()->getName() == item_name) {
//				return traversal_ptr->getItem();
//			}
//
//			traversal_ptr = traversal_ptr->getNext();
//		}
//
//		if (traversal_ptr->getItem()->getName() == item_name) {
//			return traversal_ptr->getItem();
//		}
//	}
//
//	return nullptr;
//}

void C_Inventory::update() { }
void C_Inventory::render() { }
void C_Inventory::about() { }