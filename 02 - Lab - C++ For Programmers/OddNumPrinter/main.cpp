/* 
Task 02 - C++ for Programming
Thomas Horsley -- 103071494 
31/07/23 
*/

#include<iostream>
using namespace std;

void printOddNum(int max) {
	for (int i = 0; i < max; i++) {
		if (i % 2 == 1) {
			cout << i << " ";
		}
	}
}

int main() {
	int max = 20;
	printOddNum(max);
}