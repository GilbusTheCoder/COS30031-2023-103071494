#include <iostream>
#include <vector>
#include <chrono>

class Node {
private:
	int _value;
	Node* _next;

public:
	Node(int value = 0, Node* next = nullptr) {
		_value = value;
		_next = next;
	}

	Node* getNext() { return _next; }
	int getValue() { return _value; }
	void setNext(Node* next) { _next = next; }
	void setValue(int value) { _value = value; }

	void show() { std::cout << "Value: " << _value << std::endl; }
};

class LinkedList {
private:
	Node* _head;
	int _size = 0;

public:
	LinkedList(Node* head = nullptr) {
		_head = head;
		if (head != nullptr) { _size++; }
	}

	Node* getTail() {
		Node* traversal_ptr = _head;

		while (traversal_ptr->getNext() != nullptr) {
			traversal_ptr = traversal_ptr->getNext();
		}

		return traversal_ptr;
	}

	Node* findNodeAtPos(int position) {
		Node* traversal_ptr = _head;
		
		for (int i = 0; i < position < _size; i++) {
			traversal_ptr = traversal_ptr->getNext();
		}

		return traversal_ptr;
	}

	Node* findNodeContaining(int value) {
		Node* traversal_ptr = _head;

		while (traversal_ptr->getValue() != value 
			&& traversal_ptr->getNext() != nullptr) 
		{ 
			traversal_ptr = traversal_ptr->getNext(); 
		}

		return traversal_ptr;
	}

	void addNodeToTail(int value) {
		Node* tail = getTail();
		Node* next = new Node(value);
			
		tail->setNext(next);
		_size++;
	}

	void addNode(int value, int position) {}
	void deleteNodeContaining(int value) {}

	void show() {
		Node* traversal_ptr = _head;

		while (traversal_ptr != nullptr) {
			std::cout << "Node address: " << &traversal_ptr << std::endl;
			std::cout << "Node value: " << traversal_ptr->getValue() << std::endl;

			traversal_ptr = traversal_ptr->getNext();
		}
	}
};

int main(){
	Node* init_node = new Node(4);
	LinkedList list(init_node);

	list.addNodeToTail(8);
	list.addNodeToTail(16);
	
	list.show();

	Node* test = list.findNodeAtPos(1);
	return 0;
}