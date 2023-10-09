/*	Task 13: Composite and Component Patterns
*	Author: Thomas Horsley 103071494		*/

/*	Ok, so after a smidge of thought (not too much though) I'm going to
*	integrate the ECS into zorkish such that when specific components are
*	attached to an entity, specific actions become 'unlocked'.
* 
*	Such as a movement component for go and look commands, an inventory comp for
*	taking and dropping items and a weapon component for attacking commands. 
* 
*	Another possibly is a stats component and then some systems can be designed
*	around that.																*/

#include "../hdr/StateManager.h"

// YOU WERE WORKING ON THE INVENTORY AGAIN RN

int main() {
	StateManager _game_manager;

	while (_game_manager.isRunning()) {
		_game_manager.update();
		_game_manager.render();
	}

	return 0;
}