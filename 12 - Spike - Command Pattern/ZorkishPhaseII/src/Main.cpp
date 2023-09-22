/*	Task 08 - Game State Management
*	Author 
*
*	The state manager was built implementing the OO State pattern.
*	See spike report! */

#include "../hdr/StateManager.h"

/*	1. Create a functioning inventory system which allows for adding and removing items
*	2. Create a set of location nodes connected through edges which can be traversed
*	3. Create save and load functionality
*	4. Create our command pattern												*/

int main() {
	StateManager _game_manager;

	while (_game_manager.isRunning()) {
		_game_manager.update();
		_game_manager.render();
	}

	return 0;
}