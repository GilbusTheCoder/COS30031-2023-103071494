#include <iostream>
#include "StateManager.h"

//State manager definitions
StateManager::StateManager() {
	_current_ptr->render();
}

bool StateManager::isRunning() { return _current_state != STATES::QUIT; }

void StateManager::update() {
	//Wrapped up all nice and cozy
	_current_state = _current_ptr->update();
	
	if (_current_state == STATES::MAIN_MENU) { _current_ptr = &_main_menu; }
	else if (_current_state == STATES::ABOUT) { _current_ptr = & _about_menu; }
	else if (_current_state == STATES::HELP) { _current_ptr = &_help_menu; }
	else if (_current_state == STATES::SELECT_ADVENTURE) { _current_ptr = &_adventure_select_menu; }
	else if (_current_state == STATES::GAMEPLAY) { _current_ptr = &_gameplay; }
	else if (_current_state == STATES::NEW_HS) { _current_ptr = &_new_highscore_menu; }
	else if (_current_state == STATES::VIEW_HoF) { _current_ptr = &_hall_of_fame_menu; }
	else if (_current_state == STATES::QUIT) { _current_ptr = &_quit; }

}

void StateManager::render() { _current_ptr->render(); }

//Main menu definitions
STATES MainMenu::update() {
	int choice;
	std::cin >> choice;

	std::cout << std::endl;

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
	return STATES::MAIN_MENU; 
}
void AboutMenu::render() {
	std::cout << "Written by: Thomas Horsley (103071494)" << std::endl;
	system("pause");
	std::cout << std::endl;
}


//Help menu definitions
STATES HelpMenu::update() { return STATES::MAIN_MENU; }
void HelpMenu::render() {
	std::cout << "The following commands are supported: " << std::endl;
	std::cout << ">> quit" << std::endl << ">> highscore (for testing)" << std::endl;
	system("pause");
	std::cout << std::endl;
}


//Select Adventure definitions
STATES AdventureSelectMenu::update() {
	int choice;
	std::cin >> choice;
	std::cout << std::endl;

	switch (choice) {
	case 1:
		std::cout << "This is a pretty neat world" << std::endl;
		return STATES::GAMEPLAY;
	case 2:
		std::cout << "Wow this worlds pretty cewl" << std::endl;
		return STATES::GAMEPLAY;
	case 3:
		std::cout << "This is the coolest shit i've ever seen :O" << std::endl;
		return STATES::GAMEPLAY;
	}
}

void AdventureSelectMenu::render() {
	std::cout << std::endl << "Zork(ish) :: Select Adventure " << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;
	
	std::cout << std::endl << ">> 1. World" << std::endl;
	std::cout << ">> 2. Cool World" << std::endl;
	std::cout << ">> 3. Even COOLER World" << std::endl;
}


//Gameplay state definitions
STATES GameplayState::update() {
	std::string command;
	std::cin >> command;

	if (command == "highscore") { return STATES::NEW_HS; }
	else if (command == "quit") { return STATES::QUIT; }
	else { return STATES::GAMEPLAY; }
}
void GameplayState::render() {
	std::cout << std::endl;
	std::cout << "Gameplay stuff goes in here!" << std::endl;
	std::cout << "Allowed stage 1 commands can be found in the help screen" << std::endl;
	std::cout << "Please enter test commands" << std::endl;
	std::cout << ">> ";
}


//New Highscore state definitions
STATES NewHighScoreMenu::update() { 
	std::string name;
	std::cin >> name;

	return STATES::MAIN_MENU; 
}
void NewHighScoreMenu::render() {
	std::cout << std::endl << "Zork(ish) :: Select Adventure " << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl << std::endl;
	
	std::cout << "Holy... someone's jacked and cracked at zorkish, NEW HIGHSCORE!" << std::endl << std::endl;
	
	std::cout << "World: [World here]" << std::endl;
	std::cout << "Score: [Score here]" << std::endl;
	std::cout << "Moves: [Move count here]" << std::endl << std::endl;
	
	std::cout << "Please type your name and press 'Enter': " << std::endl;
	std::cout << ">> ";
}


//Hall of fame definitions
STATES HallOfFameMenu::update() { return STATES::MAIN_MENU; }
void HallOfFameMenu::render() {
	std::cout << std::endl << "Zork(ish) :: Select Adventure " << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl << std::endl;

	std::cout << "1. [Name], [World], [Score]" << std::endl;
	std::cout << "2. [Name], [World], [Score]" << std::endl;
	std::cout << "3. [Name], [World], [Score]" << std::endl;
	std::cout << "4. [Name], [World], [Score]" << std::endl;
	std::cout << "5. [Name], [World], [Score]" << std::endl;
	std::cout << "6. [Name], [World], [Score]" << std::endl;
	std::cout << "7. [Name], [World], [Score]" << std::endl;
	std::cout << "8. [Name], [World], [Score]" << std::endl;
	std::cout << "9. [Name], [World], [Score]" << std::endl;
	std::cout << "10. [Name], [World], [Score]" << std::endl << std::endl;

	system("pause");
	std::cout << std::endl;
}


//Quit state definitions
STATES QuitState::update() { return STATES::QUIT; }
void QuitState::render() { std::cout << "Quitting zorkish!" << std::endl; }