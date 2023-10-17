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
	if (_command_factory != nullptr) {
		delete _command_factory;
		_command_factory = nullptr;
	}

	_command_factory = new CommandFactory();
}

GameplayState::~GameplayState() {
	if (_game_data != nullptr) {
		delete _game_data;
		_game_data = nullptr;
	}

	if (_command_factory != nullptr) {
		delete _command_factory;
		_command_factory = nullptr;
	}
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

std::vector<std::string> GameplayState::handleInput() {
	std::vector<std::string> command_args;
	std::stringstream input = getInput();

	while (input.good()) {
		std::string command_arg;
		input >> command_arg;
		command_args.emplace_back(command_arg);
	}

	for (std::string& arg : command_args) {
		std::transform(arg.begin(), arg.end(), arg.begin(), std::tolower);
	}

	return command_args;
}

CommandType GameplayState::validateCommandType(std::string c_type) {
	if (!c_type.empty()) {
		std::transform(c_type.begin(), c_type.end(), c_type.begin(), std::tolower);
	}
	//	Instantiating aliases is just refactoring this piece of code here to read from a map
	//	containing a valid command and a string of aliases which can be added to, just got to
	//	check for command collisions when adding.
	if (c_type == "move" || c_type == "head" || c_type == "go" ||
		c_type == "m" || c_type == "g") {
		return CommandType::MOVE;

	}
	else if (c_type == "take" || c_type == "grab" || c_type == "t") {
		return CommandType::TAKE;

	}
	else if (c_type == "drop" || c_type == "discard" || c_type == "d") {
		return CommandType::DROP;

	}
	else if (c_type == "look" || c_type == "l") {
		return CommandType::LOOK;

	}
	else if (c_type == "show" || c_type == "sh" || c_type == "s") {
		return CommandType::SHOW;

	}
	else if (c_type == "help" || c_type == "h") {
		return CommandType::HELP;

	}
	else if (c_type == "quit" || c_type == "q") {
		return CommandType::QUIT;

	}
	else {
		return CommandType::INVALID;
	}
}

std::queue<Command*> GameplayState::createCommands(std::vector<std::string> command_data) {
	std::queue<Command*> commands;

	//	Simple commands (Think "Help" and "Quit")
	if (command_data.size() == 1) {
		CommandType c_type = validateCommandType(command_data[0]);

		commands =
			_command_factory->createCommands(_game_data, c_type);
	}

	//	Command instantiation requiring args
	if (command_data.size() > 1) {
		CommandType c_type = validateCommandType(command_data[0]);

		if (!CommandType::INVALID) {
			command_data.erase(command_data.begin());
			command_data.shrink_to_fit();

			for (std::string arg : command_data) {
				std::transform(arg.begin(), arg.end(), arg.begin(), std::tolower);
			}

			/*	Command data is just a split set of everything entered except the
			*	first word	*/
			commands =
				_command_factory->createCommands(_game_data, c_type, command_data);
		}
	}

	return commands;
}



/******************************************************************************
*							   Base Class Overrides
******************************************************************************/
void GameplayState::setStateData(GameData* game_data, std::vector<std::string> args) {
	if (game_data != nullptr) { _game_data = game_data; }
}

STATES GameplayState::update() {
	if (!_game_data->is_running) { return STATES::S_QUIT; }
	std::vector<std::string> command_data = handleInput();
	std::queue<Command*> frame_commands = createCommands(command_data);

	while (!frame_commands.empty()) {
		frame_commands.front()->execute();
		frame_commands.pop();
	}

	return STATES::S_GAMEPLAY;
}

/*	If i wasn't so mentally done with this assignment i'd structure the map in such
*	a way that the current locations renderers is always the first but idrc at this
*	point																		*/
void GameplayState::render() {
	if (_game_data->is_running) {
		std::cout << "\n--------------------------------------------------\n";
		std::string current_loc_renderer = _game_data->current_location;
		current_loc_renderer.append("A");
		_game_data->c_renderers.find(current_loc_renderer)->second->render();

		std::cout << "\n--------------------------------------------------\n";
		for (auto renderer : _game_data->c_renderers) {
			if (renderer.second->renderThis() && renderer.first != current_loc_renderer) {
				_altered_renderers.emplace_back(renderer.first);
				renderer.second->render();
			}
		}

		std::cout << ">>";

		// Reset this frames altered renderer data after use
		for (std::string render_id : _altered_renderers) {
			_game_data->c_renderers.find(render_id)->second->flagForRender(false);
		}
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