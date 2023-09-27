#include <sstream>
#include "../hdr/States.h"

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
	std::cout << std::endl;
	std::cout << "--- VALID COMMANDS ---" << std::endl << std::endl;
	std::cout << " --> move / go / head" << std::endl;
	std::cout << "      - use to change location: 'go [direction]'." << std::endl;
	std::cout << " --> take / grab" << std::endl;
	std::cout << "      - add item to inventory: 'take [item name]'." << std::endl;
	std::cout << " --> drop / discard" << std::endl;
	std::cout << "      - remove item from inventory: 'drop [item name]'." << std::endl;
	std::cout << " --> look / look at" << std::endl;
	std::cout << "      - examine item in location: 'look {at} [item_name]'." << std::endl;
	std::cout << "      - E.g. look at twigs / l pot of testing / look around" << std::endl;
	std::cout << " --> show" << std::endl;
	std::cout << "      - gives player access to menus: 'show [menu]'." << std::endl;
	std::cout << "      - E.g. show inventory / sh help" << std::endl;
	std::cout << " --> quit" << std::endl;
	std::cout << "      - sends the game into the QuitState." << std::endl;
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
	if (_command_factory) { 
		delete _command_factory; _command_factory = nullptr; }
}


/******************************************************************************
*							    Rendate Stuff
******************************************************************************/
STATES GameplayState::update() {
	if (game_data->quit) { return STATES::QUIT; }
	
	handleInput();
	std::cout << std::endl;

	if (!_command_args.empty() || _command_type != "quit") {
		std::queue<Command*> frame_commands = 
			_command_factory->createCommands(_command_type, _command_args);
	
		 while (!frame_commands.empty()) {
			 frame_commands.front()->execute(game_data, _command_args);
			 frame_commands.pop();
		}
		return STATES::GAMEPLAY;
	}
	if (_command_type == "quit") {
		return STATES::QUIT;
	}
}

void GameplayState::render() {
	std::cout << std::endl;
	std::cout << game_data->current_location->getDescription() << std::endl;
	std::cout << ">> ";
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

	// Check for 1 word commands.
	if (_command_args.size() == 1) {
		_command_type = _command_args[0];

		if (validateCommandType()) {
			_command_args.clear();
			_command_args.shrink_to_fit();
		}
	}	
	// Check input is good containing at least 2 elements.
	else if (_command_args.size() > 1) {
		// Set command type to first element and clear it leaving only args
		std::vector<std::string>::iterator command_it = _command_args.begin();;
		_command_type = *command_it;
		if (validateCommandType()) {
			_command_args.erase(command_it);
			_command_args.shrink_to_fit();
			validateCommandArgs();
		}
	} else { _command_args.clear(); _command_args.shrink_to_fit(); }
}

std::stringstream GameplayState::getInput() {
	std::string input;
	getline(std::cin, input);
	std::stringstream input_stream(input);

	return input_stream;
}

// Honestly should probably be the job of the command factory but hey, it's here now
bool GameplayState::validateCommandType() {
	if (!_command_type.empty()) {
		std::transform(_command_type.begin(), _command_type.end(), _command_type.begin(), std::tolower);
	
		//	Instantiating aliases is just refactoring this piece of code here to read from a map
		//	containing a valid command and a string of aliases which can be added to, just got to
		//	check for command collisions when adding.
		if (_command_type == "move" || _command_type == "head" || _command_type == "go" ||
			_command_type == "m" || _command_type == "g") {	_command_type = "move"; }
		else if (_command_type == "take" || _command_type == "grab" || 
			_command_type == "t") {	_command_type = "take";	}
		else if (_command_type == "drop" || _command_type == "discard" || _command_type == "d") {
			_command_type = "drop";	}
		else if (_command_type == "look" || _command_type == "l") { _command_type = "look"; }
		else if (_command_type == "show" || _command_type == "sh" || _command_type == "s") {
			_command_type = "show";	}
		else if (_command_type == "help" || _command_type == "h") { _command_type = "help"; }
		else if (_command_type == "quit" || _command_type == "q") { _command_type = "quit"; }
		else { _command_type = ""; }

		if (_command_type != "") { return true; }
		return false;
	}
}

void GameplayState::validateCommandArgs() {
	for (std::string& argument : _command_args) {
		std::transform(argument.begin(), argument.end(), argument.begin(), std::tolower);
	}
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
