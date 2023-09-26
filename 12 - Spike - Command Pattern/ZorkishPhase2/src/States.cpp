#include <sstream>
#include "../hdr/States.h"
#include "../hdr/Command.h"

/******************************************************************************
*							   Main Menu State
*******************************************************************************
*							    Rendate Stuff
******************************************************************************/
STATES MainMenu::update() {
	int choice = 0;
	std::cin >> choice;

	if (!std::cin.fail()) {
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
	else {
		std::cout << "Enter a value which correlates with a menu option." << std::endl << std::endl;

		std::cin.clear();
		std::cin.ignore();
		return STATES::MAIN_MENU;
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
*							   About Menu State
*******************************************************************************
*							    Rendate Stuff
******************************************************************************/
STATES AboutMenu::update() {
	return STATES::MAIN_MENU;
}
void AboutMenu::render() {
	std::cout << "Written by: Thomas Horsley (103071494)" << std::endl;
	system("pause");
	std::cout << std::endl;
}


/******************************************************************************
*							   Help Menu State
*******************************************************************************
*							    Rendate Stuff
******************************************************************************/
STATES HelpMenu::update() { return STATES::MAIN_MENU; }
void HelpMenu::render() {
	std::cout << "The following commands are supported: " << std::endl;
	std::cout << ">> quit" << std::endl << ">> highscore (for testing)" << std::endl;
	system("pause");
	std::cout << std::endl;
}


/******************************************************************************
							Select Adventure State
*******************************************************************************
*							    De/Constructors
******************************************************************************/
AdventureSelectMenu::AdventureSelectMenu() :_world_loader(nullptr) {}
AdventureSelectMenu::~AdventureSelectMenu() {
	if (_world_loader != nullptr) { delete _world_loader; }
}

void AdventureSelectMenu::deleteLoader() {
	delete _world_loader;
	_world_loader = nullptr;
}

/******************************************************************************
*							    Rendate Stuff
******************************************************************************/
// Needs to be modified such that it does work on the gameplay state
STATES AdventureSelectMenu::update() {
	int choice;
	std::cin >> choice;

	if (!std::cin.fail()) {			// .fail() for typecheck
		std::cout << std::endl;

		switch (choice) {
		case 1:
			_world_loader = new WorldLoader("saves/test_save.txt");
			game_data = _world_loader->loadWorldData();
			
			return STATES::GAMEPLAY;
		case 2:
			std::cout << "Wow this worlds pretty cewl" << std::endl;
			return STATES::GAMEPLAY;
		case 3:
			std::cout << "This is the coolest world i've ever seen :O" << std::endl;
			return STATES::GAMEPLAY;
		}
	}

	else {
		std::cin.clear();
		std::cin.ignore();
		return STATES::SELECT_ADVENTURE;
	};
}

void AdventureSelectMenu::render() {
	std::cout << std::endl << "Zork(ish) :: Select Adventure " << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;

	std::cout << std::endl << ">> 1. World (The loading one)" << std::endl;
	std::cout << ">> 2. Cool World" << std::endl;
	std::cout << ">> 3. Even COOLER World" << std::endl;
}



/******************************************************************************
								Gameplay State
*******************************************************************************
*							    De/Constructors
******************************************************************************/
GameplayState::GameplayState() {}

GameplayState::~GameplayState() {
	if (game_data) { delete game_data; game_data = nullptr; }
}


/******************************************************************************
*							    Rendate Stuff
******************************************************************************/
STATES GameplayState::update() {
	handleInput();

	if (!_command_args.empty()) {
		Command* new_move = new MoveCommand();
		new_move->execute(game_data, _command_args);
	}
	return STATES::GAMEPLAY;
}

void GameplayState::render() {
	std::cout << "rendered gameplay " << std::endl;
	game_data->current_location->about();
}

/******************************************************************************
*							    Command Stuff
******************************************************************************/
/* Will update the _command_type and _command_args each update cycle		*/
void GameplayState::handleInput() {
	resetCommandData();
	std::stringstream input = getInput();

	// Read the input and decompose into tokens
	while (input.good()) {
		std::string input_token;
		input >> input_token;
		_command_args.emplace_back(input_token);
	}

	// Set command type to first element and clear it leaving only args
	std::vector<std::string>::iterator command_it = _command_args.begin();;
	_command_type = *command_it;
	_command_args.erase(command_it);
	_command_args.shrink_to_fit();
}

std::stringstream GameplayState::getInput() {
	std::string input;
	getline(std::cin, input);
	std::stringstream input_stream(input);

	return input_stream;
}

void GameplayState::resetCommandData() {
	_command_args.clear();
	_command_args.shrink_to_fit();
	_command_type.clear();
	_command_type.shrink_to_fit();
}

/******************************************************************************
*							   Highscore State
*******************************************************************************
*							    Rendate Stuff
******************************************************************************/
STATES NewHighScoreMenu::update() {
	std::string name;
	std::cin >> name;

	return STATES::MAIN_MENU;
}
void NewHighScoreMenu::render() {
	std::cout << std::endl << "Zork(ish) :: Select Adventure " << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl
		<< std::endl;
	std::cout << "Holy... someone's jacked and cracked at zorkish, NEW HIGHSCORE!" << std::endl
		<< std::endl;
	std::cout << "World: [World here]" << std::endl;
	std::cout << "Score: [Score here]" << std::endl;
	std::cout << "Moves: [Move count here]" << std::endl << std::endl;

	std::cout << "Please type your name and press 'Enter': " << std::endl;
	std::cout << ">> ";
}


/******************************************************************************
*							 Hall of Fame State
*******************************************************************************
*							    Rendate Stuff
******************************************************************************/
STATES HallOfFameMenu::update() { return STATES::MAIN_MENU; }
void HallOfFameMenu::render() {
	std::cout << std::endl << "Zork(ish) :: Select Adventure " << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl
		<< std::endl;
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
*								 Quit State
*******************************************************************************
*							    Rendate Stuff
******************************************************************************/
STATES QuitState::update() { return STATES::QUIT; }
void QuitState::render() { std::cout << "Quitting zorkish!" << std::endl; }
