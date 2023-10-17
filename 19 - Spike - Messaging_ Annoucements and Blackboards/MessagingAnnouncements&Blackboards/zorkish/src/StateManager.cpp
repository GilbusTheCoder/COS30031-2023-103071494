#include "../hdr/StateManager.h"

//State manager definitions
StateManager::StateManager() {
	_current_ptr->render();
}

bool StateManager::isRunning() { return _current_state != STATES::S_QUIT; }
void StateManager::update() {
	//Wrapped up all nice and cozy
	_current_state = _current_ptr->update();

	if (_current_state == STATES::S_MAIN_MENU) { _current_ptr = &_main_menu; }
	else if (_current_state == STATES::S_ABOUT) { _current_ptr = &_about_menu; }
	else if (_current_state == STATES::S_HELP) { _current_ptr = &_help_menu; }
	else if (_current_state == STATES::S_SELECT_ADVENTURE) { _current_ptr = &_adventure_select_menu; }
	else if (_current_state == STATES::S_GAMEPLAY) {
		if (_current_ptr->_game_data != nullptr) {
			GameData* game_data_frame = _current_ptr->_game_data;

			_current_ptr = &_gameplay;
			_current_ptr->setStateData(game_data_frame);
		}
	}

	else if (_current_state == STATES::S_NEW_HS) { _current_ptr = &_new_hs_menu; }
	else if (_current_state == STATES::S_VIEW_HoF) { _current_ptr = &_hall_of_fame_menu; }
	else if (_current_state == STATES::S_QUIT) { _current_ptr = &_quit; }

}

void StateManager::render() { _current_ptr->render(); }