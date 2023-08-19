#include <iostream>
#include <algorithm>
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
*/

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

class Inventory {
private:
	/*	This vector will store item pointers as we expect to do a decent bit of
		copying and resizing so it's probably more effecient even though our 
		object exist in a contiguous memory chunk */

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
		_container.shrink_to_fit(); */
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
	}*/

	void test() {
		if (true) {
			std::cout << "Vector size: " << _container.size() << std::endl;
			std::cout << "Vector capacity: " << _container.capacity() << std::endl;
			std::cout << "Vector max size: " << _container.max_size() << std::endl;
		}
	}
};

int main() {
	Item testStick("Beeeeg Testing Stick", "testType", "Good for testing data structures.");
	Inventory inventory;

	inventory.addItem(&testStick);
	inventory.test();
	inventory.printItems();
	inventory.removeItem(&testStick);
	inventory.printItems();
	inventory.test();
	return 0;
}