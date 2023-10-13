#include "../hdr/StateManager.h"

/*****************************************************************************
*								State Manager
*****************************************************************************/
StateManager::StateManager() { _current_ptr->render(); }
bool StateManager::isRunning() { return _current_state != STATES::QUIT; }

void StateManager::update() {
	//Wrapped up all nice and cozy
	_current_state = _current_ptr->update();

	if (_current_state == STATES::MAIN_MENU) { _current_ptr = &_main_menu; }
	else if (_current_state == STATES::ABOUT) { _current_ptr = &_about_menu; }
	else if (_current_state == STATES::HELP) { _current_ptr = &_help_menu; }
	else if (_current_state == STATES::SELECT_ADVENTURE) {
		_current_ptr = &_adventure_select_menu;
	}
	else if (_current_state == STATES::GAMEPLAY) {
		_game_data = _current_ptr->game_data;
		_current_ptr = &_gameplay;
		_current_ptr->game_data = _game_data;
	}
	else if (_current_state == STATES::NEW_HS) { _current_ptr = &_new_hs_menu; }
	else if (_current_state == STATES::VIEW_HoF) { _current_ptr = &_hall_of_fame_menu; }
	else if (_current_state == STATES::QUIT) { _current_ptr = &_quit; }
}

void StateManager::render() { _current_ptr->render(); }