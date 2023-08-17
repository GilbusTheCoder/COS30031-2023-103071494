#include <iostream>
#include "StateManager.h"

//State manager definitions
StateManager::StateManager() {
	_main_menu.render();
}

bool StateManager::isRunning() { return _current_state != STATES::FINISHED; }

void StateManager::update() {
	if (_current_state == STATES::MAIN_MENU) { _current_ptr = &_main_menu; }
	else if (_current_state == STATES::ABOUT) { _current_ptr = & _about_menu; }
	else if (_current_state == STATES::HELP) { _current_ptr = &_help_menu; }
	else if (_current_state == STATES::SELECT_ADVENTURE) { _current_ptr = &_adventure_select_menu; }
	else if (_current_state == STATES::GAMEPLAY) { _current_ptr = &_gameplay; }
	else if (_current_state == STATES::NEW_HS) { _current_ptr = &_new_highscore_menu; }
	else if (_current_state == STATES::VIEW_HoF) { _current_ptr = &_hall_of_fame_menu; }
	else if (_current_state == STATES::QUIT) { _current_ptr = &_quit; }

	//Wrapped up all nice and cozy
	_current_state = _current_ptr->update();
}

void StateManager::render() {
	_current_ptr->render();
}

//Main menu definitions
STATES MainMenu::update() {
	int choice;
	std::cin >> choice;

	switch (choice) {
	case 1:
		return STATES::SELECT_ADVENTURE;
	case 2:
		return STATES::VIEW_HoF;
	case 3:
		return STATES::HELP;
	case 4:
		return STATES::ABOUT;
	case 5:
		return STATES::QUIT;
	default:
		return STATES::MAIN_MENU;
	}

	return STATES::ABOUT; 
}

void MainMenu::render() { 
	std::cout << "Zork(ish) :: Main Menu" << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;
	
	std::cout << std::endl << "Welcome to Zorkish Adventures!" << std::endl;
	
	std::cout << std::endl << "1. Select Adventure and Play" << std::endl;
	std::cout  << "2. View Hall of Fame" << std::endl;
	std::cout << "3. Help" << std::endl;
	std::cout << "4. About" << std::endl;
	std::cout << "5. Quit" << std::endl;

	std::cout << std::endl << "Selected 1-5: " << std::endl;
}


//About menu definitions
STATES AboutMenu::update() { 
	system("pause");
	return STATES::MAIN_MENU; 
}
void AboutMenu::render() {
	std::cout << "Written by: Thomas Horsley (103071494)" << std::endl;
	std::cout << "Press 'Enter' to return to the Main Menu" << std::endl;
}


//Help menu definitions
STATES HelpMenu::update() { return STATES::SELECT_ADVENTURE; }
void HelpMenu::render() {
	std::cout << "The following commands are supported: " << std::endl;
	std::cout << ">> list commands here" << std::endl;
}


//Select Adventure definitions
STATES AdventureSelectMenu::update() { return STATES::GAMEPLAY; }
void AdventureSelectMenu::render() {
	std::cout << "Choose your world!" << std::endl;
}


//Gameplay state definitions
STATES GameplayState::update() { return STATES::NEW_HS; }
void GameplayState::render() {
	std::cout << "Gameplay stuff goes in here!" << std::endl;
}


//New Highscore state definitions
STATES NewHighScoreMenu::update() { return STATES::VIEW_HoF; }
void NewHighScoreMenu::render() {
	std::cout << "Holy someone's jacked and cracked at zorkish, NEW HIGHSCORE!" << std::endl;
}


//Hall of fame definitions
STATES HallOfFameMenu::update() { return STATES::QUIT; }
void HallOfFameMenu::render() {
	std::cout << "Look at this poor empty Hall of fame :'(" << std::endl;
}


//Quit state definitions
STATES QuitState::update() { return STATES::FINISHED; }
void QuitState::render() { std::cout << "Quitting zorkish!" << std::endl; }