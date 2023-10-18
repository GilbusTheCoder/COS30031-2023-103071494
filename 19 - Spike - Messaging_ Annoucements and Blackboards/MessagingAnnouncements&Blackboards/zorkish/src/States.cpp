#include <iostream>
#include <string>
#include <sstream>
#include "../hdr/States.h"

/******************************************************************************
*							       MAIN MENU
*								  DEFINITIONS
*
/******************************************************************************
*							  base class overrides
******************************************************************************/
void MainMenu::setStateData(GameData* game_data,
	std::vector<std::string> args) {
}

STATES MainMenu::update() {
	int choice = 0;
	std::cin >> choice;

	if (!std::cin.fail()) {
		std::cout << std::endl;

		switch (choice) {
		case 1:
			return STATES::S_SELECT_ADVENTURE;
		case 2:
			return STATES::S_VIEW_HoF;
		case 3:
			return STATES::S_HELP;
		case 4:
			return STATES::S_ABOUT;
		case 5:
			return STATES::S_QUIT;
		default:
			return STATES::S_MAIN_MENU;
		}
	}
	else {
		std::cout << "Enter a value which correlates with a menu option." << std::endl << std::endl;

		std::cin.clear();
		std::cin.ignore();
		return STATES::S_MAIN_MENU;
	}

}

void MainMenu::render() {
	std::cout << "Zork(ish) :: Main Menu" << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;

	std::cout << std::endl << "Welcome to Zorkish Adventures!" << std::endl;

	std::cout << std::endl << "1. Select Adventure and Play" << std::endl;
	std::cout << "2. View Hall of Fame" << std::endl;
	std::cout << "3. Help" << std::endl;
	std::cout << "4. About" << std::endl;
	std::cout << "5. Quit" << std::endl;

	std::cout << std::endl << "Selected 1-5: " << std::endl;
}



/******************************************************************************
*							      ABOUT MENU
*								  DEFINITIONS
*
/******************************************************************************
*							  base class overrides
******************************************************************************/
void AboutMenu::setStateData(GameData* game_data,
	std::vector<std::string> args) { }

STATES AboutMenu::update() {
	return STATES::S_MAIN_MENU;
}
void AboutMenu::render() {
	std::cout << "Written by: Thomas Horsley (103071494)" << std::endl;
	system("pause");
	std::cout << std::endl;
}



/******************************************************************************
*								   HELP MENU
*								  DEFINITIONS
*
/******************************************************************************
*							  base class overrides
******************************************************************************/
void HelpMenu::setStateData(GameData* game_data,
	std::vector<std::string> args) { }

STATES HelpMenu::update() { return STATES::S_MAIN_MENU; }
void HelpMenu::render() {
	std::cout << "The following commands are supported: " << std::endl;
	std::cout << ">> quit" << std::endl << ">> highscore (for testing)" << std::endl;
	system("pause");
	std::cout << std::endl;
}



/******************************************************************************
*							ADVENTURE SELECT MENU
*								  DEFINITIONS
*
/******************************************************************************
*							    De/Constructors
******************************************************************************/
AdventureSelectMenu::AdventureSelectMenu() {
	if (_world_loader == nullptr) { _world_loader = new WorldLoader(); }
}

AdventureSelectMenu::~AdventureSelectMenu() {
	if (_world_loader != nullptr) {
		delete _world_loader;
		_world_loader = nullptr;
	}
}



/******************************************************************************
*							    Base Class Overrides
******************************************************************************/
void AdventureSelectMenu::setStateData(GameData* game_data, std::vector<std::string> args) { }

STATES AdventureSelectMenu::update() {
	int choice;
	std::cin >> choice;

	if (!std::cin.fail()) {
		std::cout << std::endl;

		switch (choice) {
		case 1:
			_world_loader->setSaveFile("Zorkish/saves/test_save.txt");
			_game_data = _world_loader->loadGameData();
			return STATES::S_GAMEPLAY;
		case 2:
			std::cout << "Wow this worlds pretty cewl. Too bad it doesnt load"
				<< std::endl;
			return STATES::S_SELECT_ADVENTURE;
		case 3:
			std::cout << "This is the coolest non-functional world i've ever seen!"
				<< std::endl;
			return STATES::S_SELECT_ADVENTURE;
		}
	}

	else {
		std::cout << "Please enter a value correlating with the options" << std::endl << std::endl;

		std::cin.clear();
		std::cin.ignore();
	};
	return STATES::S_SELECT_ADVENTURE;
}

void AdventureSelectMenu::render() {
	std::cout << std::endl << "Zork(ish) :: Select Adventure " << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;

	std::cout << std::endl << ">> 1. World (The loading one)" << std::endl;
	std::cout << ">> 2. Cool World" << std::endl;
	std::cout << ">> 3. Even COOLER World" << std::endl;
}




/******************************************************************************
*								 GAMPLAY STATE
*								  DEFINITIONS
*
/******************************************************************************
*							    De/Constructors
******************************************************************************/
GameplayState::GameplayState() {
	if (_input_handler != nullptr) {
		delete _input_handler;
		_input_handler = nullptr; }
	
	if (_event_dispatcher != nullptr) {
		delete _event_dispatcher;
		_event_dispatcher = nullptr; }

	_input_handler = new InputHandler();
	_event_dispatcher = new EventDispatcher();
}

GameplayState::~GameplayState() {
	if (_game_data != nullptr) {
		delete _game_data;
		_game_data = nullptr; }

	if (_input_handler != nullptr) {
		delete _input_handler;
		_input_handler = nullptr; }
	
	if (_event_dispatcher != nullptr) {
		delete _event_dispatcher;
		_event_dispatcher = nullptr; }
}



/******************************************************************************
*									 Input
******************************************************************************/
std::stringstream GameplayState::getInput() {
	std::string input;
	getline(std::cin, input);
	std::stringstream input_stream(input);

	return input_stream;
}




/******************************************************************************
*							   Base Class Overrides
******************************************************************************/
void GameplayState::setStateData(GameData* game_data, std::vector<std::string> args) {
	if (game_data != nullptr) { _game_data = game_data; }
}

STATES GameplayState::update() {
	if (!_game_data->is_running) { return STATES::S_QUIT; }

	if (_game_data->reinstance_local_entity_cache) { 
		_event_dispatcher->filterLocalComponents(_game_data); }
	
	// The post office
	std::queue<Command*> events = _event_dispatcher->processEvents
		(_game_data, _input_handler->handleInput(getInput()));
	
	// Consider this the mailing system
	while (!events.empty()) {
		events.front()->triggerEvent();	
		events.pop(); }

	return STATES::S_GAMEPLAY;
}

void GameplayState::render() {
	std::map<std::string, C_Render*>::iterator traversal_it;

	for (traversal_it = _game_data->c_renderers.begin();
		traversal_it != _game_data->c_renderers.end(); ++traversal_it) {

	}
}



/******************************************************************************
*							  NEW HIGHSCORE MENU
*								  DEFINITIONS
*
/******************************************************************************
*							  base class overrides
******************************************************************************/
void NewHighScoreMenu::setStateData(GameData* game_data,
	std::vector<std::string> args) { }

STATES NewHighScoreMenu::update() {
	std::string name;
	std::cin >> name;

	return STATES::S_MAIN_MENU;
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



/******************************************************************************
*								 HALL OF FAME
*								  DEFINITIONS
*
/******************************************************************************
*							  base class overrides
******************************************************************************/
void HallOfFameMenu::setStateData(GameData* game_data,
	std::vector<std::string> args) { }

STATES HallOfFameMenu::update() { return STATES::S_MAIN_MENU; }
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



/******************************************************************************
*								  QUIT STATE
*								  DEFINITIONS
*
/******************************************************************************
*							  base class overrides
******************************************************************************/
void QuitState::setStateData(GameData* game_data,
	std::vector<std::string> args) { }
STATES QuitState::update() { return STATES::S_QUIT; }
void QuitState::render() { std::cout << "Quitting zorkish!" << std::endl; }