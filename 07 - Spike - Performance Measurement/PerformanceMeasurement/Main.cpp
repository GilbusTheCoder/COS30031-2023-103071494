#include <iostream>
#include <vector>
#include <chrono>

//class ArraySpeedTest{
//private:
//	int _size;
//	int _array[];
//
//public:
//	ArraySpeedTest(int size) {
//		_size = size;
//		_array[size] = new int(size);
//
//		fillArray();
//		printArray();
//	}
//
//	void printArray() {
//		for (int i = 0; i < _size; i++) {
//			std::cout << i << ": " << _array[i] << std::endl;
//		}
//	}
//
//	void fillArray() {
//		for (int i = 0; i < _size; i++) {
//			int test = i;
//			_array[i] = test;
//		}
//	}
//};

class Node {
private:
	int _value;
	Node* _next;

public:
	Node(int value = 0, Node* next = nullptr) {
		_value = value;
		_next = next;
	}

	//Bitch throws a read access violation cuz of nullptr gotta fix
	Node* getNext() { return _next; }
	int getValue() { return _value; }
	void setNext(Node* next) { _next = next; }
	void setValue(int value) { _value = value; }
};

class LinkedList {
private:
	Node* _head;
	int _size = 0;

public:
	LinkedList(Node* head = nullptr) {
		_head = head;

		if (head != nullptr) {
			_size++;
		}
	}


	Node* getTail() {
		Node* traversal_ptr = _head;

		while (traversal_ptr->getNext() != nullptr) {
			traversal_ptr = traversal_ptr->getNext();
		}

		return traversal_ptr;
	}

	void addNode(int value) {
		if (_head == nullptr) {
			Node* head = new Node(_size);
			_size++;
		}
		else {
			Node* tail = getTail();
			Node* next = new Node(_size);
			
			tail->setNext(next);
			_size++;
		}
	}

	void printList() {
		Node* traversal_ptr = _head;

		while (&traversal_ptr != nullptr) {
			std::cout << "Node address: " << &traversal_ptr << std::endl;
			std::cout << "Node value: " << traversal_ptr->getValue() << std::endl;

			if (traversal_ptr->getNext() == nullptr) { std::cout << "Node next: nullptr" << std::endl; }
			else { std::cout << "Node next" << traversal_ptr->getNext() << std::endl; }
			std::cout << std::endl;

			traversal_ptr = traversal_ptr->getNext();
		}
	}
};

int main(){
	Node* init_node = new Node();
	LinkedList list(init_node);

	list.printList();

	return 0;
}