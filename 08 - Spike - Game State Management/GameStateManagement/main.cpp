/*	Task 08 - Game State Management
*	Author - Thomas Horsley (103071494)
* 
*	The state manager was built implementing the OO State pattern.
*	See spike report! */

#include <iostream>
#include <string>
#include "StateManager.h"


int main() {
	StateManager _game_manager;

	while (_game_manager.isRunning()) {
		_game_manager.update();
		_game_manager.render();
	}

	return 0;
}