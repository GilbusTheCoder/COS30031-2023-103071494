#include "../header/pch.h"
#include "../header/StateManager.h"

//State manager definitions
StateManager::StateManager() {
	_current_ptr->render();
}

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
		if (!_has_loaded_save_game) { _location_data = _adventure_select_menu.returnLocationData(); }
		_current_ptr = &_gameplay; 
	}
	else if (_current_state == STATES::NEW_HS) { _current_ptr = &_new_highscore_menu; }
	else if (_current_state == STATES::VIEW_HoF) { _current_ptr = &_hall_of_fame_menu; }
	else if (_current_state == STATES::QUIT) { _current_ptr = &_quit; }
}

void StateManager::render() { _current_ptr->render(); }