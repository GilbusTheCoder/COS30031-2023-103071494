#include <iostream>
#include <fstream>

/*	Task: Lab 10
*	Title: File Input Output
*	Author: Thomas Horsley 103071494

	Part A
	TODO: 1. Create a new document for your lab notes. (Add �Part A� section heading?)
	-2. Write a C++ program that has
		a. a basic struct or class (�compound type�) that has at least 3 simple variables: char, int, float;
		b. create (or have created) an instance of your compound type, then
		c. set the value of each variable in your instance, to something other than a zero value.
	-3. Write a reusable routine (function) to print/show the values to screen.
	TODO: 4. Compile and run. Add and commit doc + code to repo 

	Part B
	- 5. Modify your code to
		a. open a binary file in �write� mode (such as �test1.bin�), then
		b. write the three different values to the binary file, and finally
		c. close the file.
			TODO: There are different file open modes: What are they? (Answer in lab notes!)
			TODO: What happens if you don�t �close� the file? Is it something we need to worry about? (Answer in lab notes!) 
*/

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
	void setChar(char character) { _char = character; }
	void setInt(int integer) { _int = integer; }
	void setFloat(float floating_pt) { _float = floating_pt; }

	void show() {
		std::cout << "Character: " << _char << std::endl;
		std::cout << "Integer: " << _int << std::endl;
		std::cout << "Float: " << _float << std::endl;
	}
};

int main() {
	CompoundType write_tester('C', 1, 3.14);
	CompoundType read_tester;
	std::ofstream writer;
	std::ifstream reader;

	if (writer) {
		writer.open("test.dat", std::ios::app | std::ios::binary);
		writer.write(reinterpret_cast<char*>(&write_tester), sizeof(CompoundType));
		writer.close();
	}

	reader.open("test.dat", std::ios::binary);
	while (reader.read(reinterpret_cast<char*>(&read_tester), sizeof(CompoundType))) {
		read_tester.show();
	};

	reader.close();
	return 0; 
}