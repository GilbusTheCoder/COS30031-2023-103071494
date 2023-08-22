#include <iostream>
#include <vector>

/*	NOTES ON VECTORS
*	- Use shrink_to_fit() after erasing or clearing values to release the allocated memory
*	- Avoid reallocation of memory by reserving the size of the vector ahead of time.
*	- When filling or copying a vector use reassignment instead of insert() or push_back loops
*		* This only requires 1 memory reallocation as the size of both vectors will (if employing
*		* point 2) are known.
* 
*		* If reassignment isn't an option than insert() is faster than push_back() loops
*	
*	- Don't use vector::at() to iterate through a function it's slow af compared to iterators
*	- Avoid inserting elements infront of the vector as this is an O(n) operation 
*		* last element insertion being O(1) operation
*	
*	- Try to use emplace_back() instead of push_back(). Though they're pretty much the same,
*	  when adding elements during construction or passing implicit types into the vector 
*	  emplace_back() is clearly favourable.
* 
*	
*	NOTES ON LINKED LISTS
*	- AHHH FUCK */

class Item {
private:
	std::string _name;
	std::string _type;
	std::string _description;

public:
	Item() {};
	Item(std::string name, std::string type, std::string description) {
		setName(name);
		setType(type);
		setDescription(description);
	}

	std::string getName() { return _name; }
	void setName(std::string name) { _name = name; }
	std::string getType(){ return _type; }
	void setType(std::string type) { _type = type; }
	std::string getDescription() { return _description; }
	void setDescription(std::string description) { _description = description; }

	void printDescription() {
		std::cout << "Name: " << _name << std::endl;
		std::cout << "Type: " << _type << std::endl;
		std::cout << "Desc: " << _description << std::endl;
	};
};

/*	The inventory item will be a collection of inventory slots all linked together
*	via a linked list data structure.
* 
*	The slot will contain a pointer to the next slot and the item address which of
*	what has been added to the inventory. If a slot is empty then the value is initialized 
*	to NULL; */
class InventorySlot{
private:
	Item* _item;
	InventorySlot* _next;

public:
	InventorySlot(Item* item_ptr, InventorySlot* next = nullptr) {
		_item = item_ptr;
		_next = next;
	};

	Item* getItem() { return _item; }
	InventorySlot* getNext() { 
		if (_next != nullptr) { return _next; }
		else { 
			InventorySlot* hack_fix = nullptr;
			return hack_fix; }
	}
	
	void setItem(Item* item_ptr) { _item = item_ptr; }
	void setNext(InventorySlot* next_ptr) { _next = next_ptr; }

	void about() {
		std::cout << "data: " << _item << std::endl;
		std::cout << "next: " << _next << std::endl;
	}
};

// The node daddy...
class Inventory {
private:
	InventorySlot* _head;
	int _size = 0;
	int _max_size = 64;


public:
	//For now inventory must be constructed with at least 1 item.
	Inventory(InventorySlot* head) {
		_head = head;
		_size++;
	}

	InventorySlot* getHead() { return _head; }

	InventorySlot* getTail() {
		InventorySlot* traversal_ptr = _head;

		while(traversal_ptr->getNext() != nullptr){
			traversal_ptr = traversal_ptr->getNext();
		}
		return traversal_ptr;
	}

	InventorySlot addItem(Item* item_ptr) {
		InventorySlot new_item = InventorySlot(item_ptr);
		InventorySlot* tail = getTail();

		tail->setNext(&new_item);
		_size++;

		return new_item;
	}

	void deleteItem(Item* item) {
		InventorySlot* previous_ptr = nullptr;
		InventorySlot* traversal_ptr = _head;

		while (traversal_ptr->getItem() != item) {
			previous_ptr = traversal_ptr;
			traversal_ptr = traversal_ptr->getNext();
		}

		previous_ptr->setNext(traversal_ptr->getNext());
		traversal_ptr->setNext(nullptr);
		_size--;
	}

	void show() {
		InventorySlot* traversal_ptr = _head;

		while (traversal_ptr != nullptr) {
			traversal_ptr->getItem()->printDescription();
			std::cout << std::endl;
			traversal_ptr = traversal_ptr->getNext();
		}
	}
};

int main() {
	Item test_stick ("Testing Stick", "testType", "Great for breaking monitors :/");
	InventorySlot init_slot(&test_stick);
	Inventory inventory(&init_slot);
	
	Item test_potion("Pot of Testing", "testType", "Good for quick fixes!");
	Item test_armour("Test Armour", "testType", "Bug armour is required for any heavy debugging.");
	
	inventory.addItem(&test_potion);
	inventory.show();

	inventory.addItem(&test_armour);
	inventory.show();

	inventory.deleteItem(&test_potion);
	inventory.show();

	return 0;
}


/*Old Vector Code from before I quit messing around with iterators
class Inventory {
private:
	/*	This vector will store item pointers as we expect to do a decent bit of
		copying and resizing so it's probably more effecient even though our 
		object exist in a contiguous memory chunk 

	std::vector<Item*> _container;
	int _inventory_capactity = 100;

public:
	Inventory() {
		_container.reserve(_inventory_capactity);
		test();
	}

	~Inventory() {
		_container.clear();
		std::vector<Item*>().swap(_container);

		/*	As far as I can tell shrink_to_fit() can sometimes be ignored by the compiler.
		*	After some research I found the above line of code which should deallocate the
		*	memory after clear(). 
		_container.shrink_to_fit(); 
	}

	void addItem(Item* item_ptr) {
		_container.emplace_back(item_ptr);
	};

	void printItems() {
		for (auto iterator = _container.begin(); iterator != _container.end(); iterator++) {
			(*iterator)->printDescription();
		}
	}

	void removeItem(Item* item_ptr) {
		for (int i = 0; i == _container.size(); i++) {
			if (*iterator == item_ptr) { _container.erase(iterator); }
		}
	}
	/*void removeItem(Item* item_ptr) {
		_container.erase(std::remove_if(_container.begin(), _container.end(),
			[](const Item* element, Item* item_ptr) {return item_ptr == element; }));
		
		_container.end();
	}

	void test() {
		if (true) {
			std::cout << "Vector size: " << _container.size() << std::endl;
			std::cout << "Vector capacity: " << _container.capacity() << std::endl;
			std::cout << "Vector max size: " << _container.max_size() << std::endl;
		}
	}
};*/