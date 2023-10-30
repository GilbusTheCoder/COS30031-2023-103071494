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
		case 1:	return STATES::S_SELECT_ADVENTURE;
		case 2:	return STATES::S_VIEW_HoF;
		case 3:	return STATES::S_HELP;
		case 4:	return STATES::S_ABOUT;
		case 5:	return STATES::S_QUIT;
		default: return STATES::S_MAIN_MENU;
		}
	} else {
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
*								   Private
******************************************************************************/
void GameplayState::resetRender() {
	std::map<std::string, C_Render*>::iterator it;

	for (it = _game_data->c_renderers.begin();
		it != _game_data->c_renderers.end(); ++it) {
		it->second->flagForRender(false);
		it->second->doShallowRender(true);

		std::string UEID = extractUEID(it->second->getUCID());
		if (UEID.front() == _game_data->current_location.front()) {
			it->second->flagForRender(true);
			it->second->doShallowRender(_game_data->discovered_area);
		}
	}
}

std::string GameplayState::extractUEID(std::string ucid) {
	// Check each character of the cuid until we hit an upper case letter
	// take all the characters from before the upper case and that's our EUID
	// to return.
	std::string::iterator cuid_it;
	std::string UEID;

	for (cuid_it = ucid.begin(); cuid_it != ucid.end(); cuid_it++) {
		if (char(*cuid_it) > 96 && char(*cuid_it) < 123) {
			std::string EUID_element(1, char(*cuid_it));
			UEID.append(EUID_element);
		}
		else { return UEID; }
	}

	return UEID;
}

/******************************************************************************
*							   Base Class Overrides
******************************************************************************/
void GameplayState::setStateData(GameData* game_data, std::vector<std::string> args) {
	if (game_data != nullptr) { _game_data = game_data; }
	if (_game_data != nullptr) { 
		_event_dispatcher->setGameData(_game_data); 
		_event_dispatcher->filterLocalComponents();
	}
}

STATES GameplayState::update() {
	if (!_game_data->is_running) { return STATES::S_QUIT; }
	
	std::string frame_start_location = _game_data->current_location;
	std::string input;
	
	getline(std::cin, input);
	std::stringstream input_stream(input);

	// The post office
	std::queue<Command*> events = _event_dispatcher->processEvents
		(_input_handler->handleInput(input_stream, _game_data));
	
	// Consider this the mailing system
	while (!events.empty()) {
		events.front()->triggerEvent();	
		events.pop(); }

	if (frame_start_location.front() != _game_data->current_location.front()) {
		_event_dispatcher->filterLocalComponents();	}
	
	return STATES::S_GAMEPLAY;
}

void GameplayState::render() {
	std::vector<C_Render*>::iterator traversal_it;

	if (first_pass) {
		for (C_Render* renderer : _game_data->_local_renderers) {
			renderer->flagForRender(false); }

		first_pass = !first_pass;
	}

	for (traversal_it = _game_data->_local_renderers.begin();
		traversal_it != _game_data->_local_renderers.end(); ++traversal_it) {
		if ((*traversal_it)->renderThis()) {
			(*traversal_it)->onEvent(); }
	}

	resetRender();
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