/*	Task: Lab 10
*	Title: File Input Output
*	Author: Thomas Horsley 103071494

	1. Create a new document for your lab notes. (Add “Part A” section heading?)
	2. Write a C++ program that has
		a. a basic struct or class (“compound type”) that has at least 3 simple variables: char, int, float;
		b. create (or have created) an instance of your compound type, then
		c. set the value of each variable in your instance, to something other than a zero value.
	3. Write a reusable routine (function) to print/show the values to screen.
	4. Compile and run. Add and commit doc + code to repo */

#include <iostream>

class CompoundType {
private:
	char _char;
	int _int;
	float _float;

public:
	CompoundType(char character = ' ', int integer = 0, float floating_pt = 0.0) {
		_char = character;
		_int = integer;
		_float = floating_pt;
	}

	char getChar() { return _char; }
	int getInt() { return _int; }
	float getFloat() { return _float; }

	void show() {
		std::cout << "Character: " << _char << std::endl;
		std::cout << "Integer: " << _int << std::endl;
		std::cout << "Float: " << _float << std::endl;
	}
};

int main() {
	CompoundType tester('C', 1, 3.14);
	tester.show();
}