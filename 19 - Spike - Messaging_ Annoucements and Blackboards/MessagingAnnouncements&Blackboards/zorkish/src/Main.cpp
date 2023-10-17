/*	Task 19 - Messaging and Announcements
*	Author - Thomas Horsley (103071494) */

#include "../hdr/StateManager.h"


int main() {
	StateManager _game_manager;

	while (_game_manager.isRunning()) {
		_game_manager.update();
		_game_manager.render();
	}

	return 0;
}