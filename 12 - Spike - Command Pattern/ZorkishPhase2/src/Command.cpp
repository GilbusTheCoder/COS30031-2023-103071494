#include "../hdr/Command.h"

/******************************************************************************
*								  Move Command
******************************************************************************/
void MoveCommand::execute(GameData* game_data, std::vector<std::string> args) {
	if (game_data->current_location->getExit(args[0]) != nullptr) {
		game_data->current_location = 
			game_data->current_location->getExit(args[0]);
	}
}



/******************************************************************************
*								  Take Command
******************************************************************************/
void TakeCommand::execute(GameData* game_data, std::vector<std::string> args) {
	// Take the full name of the item
	if (args.size() >= 1) {
		std::string item_name = determineItemName(args);
		args.insert(args.begin(), item_name); // Item name is now one string

		if (args.size() == 1) {
			Item* item = game_data->current_location->getItem(args.front());
			game_data->player->takeItem(item);
			game_data->current_location->removeItem(item);
		}

		if (args.size() > 1 && isItemEnclosed(args)) {
			// do the transfer of items from enclosure stuff
			// save for task 13
		}
	}
}

std::string TakeCommand::determineItemName(std::vector<std::string>& args) {
	//	Assumed the first command is the first word of the item name
	std::string item_name = "";
	if (!args.empty()) {
		int item_name_word_count = 0;
		//	If the arg isn't an 'in' or 'from' append it to the item_name the 
		//	item_name is returned. Args is also modified to not contain name.
		for (auto name_token : args) {
			if (name_token != "in" || name_token != "from") {
				item_name.append(name_token);
				item_name.append(" ");
				item_name_word_count++;
			}
		}

		for (int idx = 0; idx < item_name_word_count; idx++) {
			args.erase(args.begin());
			args.shrink_to_fit();
		}
	}

	return item_name.substr(0, item_name.length() - 1);
}

/*	Will return true if the player has stated take item from, take item in */
bool TakeCommand::isItemEnclosed(const std::vector<std::string>& args) {
	if (args.size() > 1 && (args[2] == "in" || args[2] == "from")) {
		return true;
	}
	return false;
}



/******************************************************************************
*								  Drop Command
******************************************************************************/
void DropCommand::execute(GameData* game_data, std::vector<std::string> args) {
	if (args.size() > 1) {
		std::string item_name = determineItemName(args);
		args.insert(args.begin(), item_name);
	}

	// If condition is met we know input was good, if we have item is handled
	// by inventory or whatever idk
	if (args.size() == 1 && game_data->player->hasItem(args[0])) {
		Item* item = game_data->player->findItem(args[0]);
		Item* item_cpy = new Item(
			item->getName(),
			item->getDescription(),
			item->getType());

		game_data->current_location->addItem(item_cpy);
		game_data->player->deleteItem(item);
	}
}

std::string DropCommand::determineItemName(std::vector<std::string>& args) {
	//	Assumed the first command is the first word of the item name
	std::string item_name = "";
	if (!args.empty()) {
		int item_name_word_count = 0;
		//	If the arg isn't an 'in' or 'from' append it to the item_name the 
		//	item_name is returned. Args is also modified to not contain name.
		for (auto name_token : args) {
			item_name.append(name_token);
			item_name.append(" ");
			item_name_word_count++;
		}

		for (int idx = 0; idx < item_name_word_count; idx++) {
			args.erase(args.begin());
			args.shrink_to_fit();
		}
	}

	return item_name.substr(0, item_name.length() - 1);
}

/******************************************************************************
*								  Look Command
******************************************************************************/
void LookCommand::execute(GameData* game_data, std::vector<std::string> args) {
	if (args[0] == "at") { args.erase(args.begin()); args.shrink_to_fit(); }
	std::string item_name = determineItemName(args);
	
	// General search
	if (item_name == "around") {
		std::cout << "You see: " << std::endl;
		game_data->current_location->showItemNames();
		return;
	}

	// Search for an item otherwise
	Item* item = game_data->current_location->getItem(item_name);
	if (item != nullptr) {
		std::cout << " --> " << item->getName() << std::endl;
		std::cout << "      - " << item->getDescription() << std::endl;
	}
}

std::string LookCommand::determineItemName(std::vector<std::string>& args) {
	//	Assumed the first command is the first word of the item name
	std::string item_name = "";
	if (!args.empty()) {
		int item_name_word_count = 0;
		//	If the arg isn't an 'in' or 'from' append it to the item_name the 
		//	item_name is returned. Args is also modified to not contain name.
		for (auto name_token : args) {
			item_name.append(name_token);
			item_name.append(" ");
			item_name_word_count++;
		}

		for (int idx = 0; idx < item_name_word_count; idx++) {
			args.erase(args.begin());
			args.shrink_to_fit();
		}
	}

	return item_name.substr(0, item_name.length() - 1);
}


/******************************************************************************
*								  Show Command
******************************************************************************/
void ShowCommand::execute(GameData* game_data, std::vector<std::string> args) {
	if (args[0] == "inventory") { game_data->player->showInventory(); return; }
	if (args[0] == "help") { showHelp(); return; }
}

void ShowCommand::showHelp() {
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
*								  Quit Command
******************************************************************************/
void QuitCommand::execute(GameData* game_data, std::vector<std::string> args) {
	game_data->quit = true; }