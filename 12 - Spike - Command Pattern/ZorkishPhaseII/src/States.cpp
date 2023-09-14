#include <typeinfo>

#include "../header/pch.h"
#include "../header/States.h"

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
	std::cout << "2. View Hall of Fame" << std::endl;
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
	system("pause"); std::cout << std::endl;
}





//Select Adventure definitions
AdventureSelectMenu::AdventureSelectMenu() {};

AdventureSelectMenu::~AdventureSelectMenu() {
	if (!_adventure_locations.empty()) {
		for (auto location : _adventure_locations) { delete location; }
	}

	if (!_world_items.empty()) {
		for (auto& [item_name, item] : _world_items) {
			delete item;
		}

		_world_items.clear();	
	}
}

// Can swap this out for something modular based off the adventure enum
// if the adventure selection becomes unweildy.
void AdventureSelectMenu::cacheSaveData(int choice ) {
	std::string file_name;

	switch (choice) {
	case 1: {file_name = "/saves/dwarf_caverns.txt"; break; }
	case 2: {file_name = "/saves/elven_capital.txt"; break; }
	case 3: {file_name = "/saves/nightmare_woods.txt"; break; }
	}

	_world_loader->openFile(file_name);
	_raw_world_data = _world_loader->getFormattedFileData();
}

// This could also be formatted to read from file but it isn't the point of the 
// spike so it's done the same as the constructLocations()
std::unordered_map<std::string, Item*> AdventureSelectMenu::constructItems(ADVENTURES current_adventure) {
	std::unordered_map<std::string, Item*> items = {};
	
	switch (current_adventure) {
	case DWARF_CAVERNS: {
		//Allocate Memory
		Item* silver_sword = new Weapon("Silver Sword", "Shiny and sharp, glimmers when twisted in the light.");
		Item* old_runed_greataxe = new Weapon("Ancient Dwarf Greataxe", "It's heavier than you expect and still sturdy.\n Runes inlay the slayer style dual-headed greataxe.");
		Item* hammerers_helmet = new Armour("Hammerers Helment", "A flat top and heavy iron sides are somewhat similar to a robust top-hat.");
		Item* hammerers_chestpiece = new Armour("Hammerers Chestpiece", "Too small for me, perfect size for the Stunty.");
		Item* old_dwarven_ale = new Consumable("Dwarven Ale", "Looks pretty stagnant, kinda yeasty, very yummy.");
		Item* old_dwarven_wine = new Consumable("Dwarven Wine", "It's already been opened and reeks of vinegar and gobbo piss");
		Item* rubbish_pile = new Misc("Rubbish Pile", "Stinks of goblin rot.");
		Item* full_coin_purse = new Misc("Full Coin Purse", "Hefty with midget gold.");
		Item* empty_coin_purse = new Misc("Empty Coin Purse", "Yet they speak only of dwarven riches... typical.");

		//Push Pointers to _world_items
		items.insert(std::pair<std::string, Item*>(silver_sword->getName(), silver_sword));
		items.insert(std::pair<std::string, Item*>(old_runed_greataxe->getName(), old_runed_greataxe));
		items.insert(std::pair<std::string, Item*>(hammerers_helmet->getName(), hammerers_helmet));
		items.insert(std::pair<std::string, Item*>(hammerers_chestpiece->getName(), hammerers_chestpiece));
		items.insert(std::pair<std::string, Item*>(old_dwarven_ale->getName(), old_dwarven_ale));
		items.insert(std::pair<std::string, Item*>(old_dwarven_wine->getName(), old_dwarven_wine));
		items.insert(std::pair<std::string, Item*>(rubbish_pile->getName(), rubbish_pile));
		items.insert(std::pair<std::string, Item*>(full_coin_purse->getName(), full_coin_purse));
		items.insert(std::pair<std::string, Item*>(empty_coin_purse->getName(), empty_coin_purse));

		return items;
	}

	case ELVEN_CAPITAL: {
		Item* silver_sword = new Weapon("Silver Sword", "Shiny and sharp, glimmers when twisted in the light.");
		Item* elven_wine = new Consumable("Lothern Wine", "High Elves love to think they're win is of much better quality than that of Bretonnian or Dwarven wine.");
		Item* elf_brew = new Consumable("Elf Brew", "Gnoblar blud tastes tastier.");
		Item* lothern_spear = new Weapon("Lothern Spear", "Head like a razor.\n Some Elf-things will train hundreds of years only to be eaten in their first skirmish...");
		Item* elven_longbow = new Weapon("High Elf Longbow", "The bowstring is without a freyed fret and the wood without a scratch.\nA fine quality bow.");
		Item* lothern_tower_shield = new Armour("Lothern Tower Shield", "Big heafty shield used for interlocking spear-walls");
		Item* elven_flute = new Misc("Elven Flute", "They can make some especially dainty tunes with these.");
		Item* fine_elven_wine_glass = new Misc("Capital Brand Wine Glass", "Glass-like in appearance with exceptional craftsmanship,\nyet won't break if dropped.");

		items.insert(std::pair<std::string, Item*>(silver_sword->getName(), silver_sword));
		items.insert(std::pair<std::string, Item*>(elven_wine->getName(), elven_wine));
		items.insert(std::pair<std::string, Item*>(elf_brew->getName(), elf_brew));
		items.insert(std::pair<std::string, Item*>(lothern_spear->getName(), lothern_spear));
		items.insert(std::pair<std::string, Item*>(elven_longbow->getName(), elven_longbow));
		items.insert(std::pair<std::string, Item*>(lothern_tower_shield->getName(), lothern_tower_shield));
		items.insert(std::pair<std::string, Item*>(elven_flute->getName(), elven_flute));
		items.insert(std::pair<std::string, Item*>(fine_elven_wine_glass->getName(), fine_elven_wine_glass));

		return items;
	}

	case NIGHTMARE_WOODS: {
		Item* silver_sword = new Weapon("Silver Sword", "Shiny and sharp, glimmers when twisted in the light.");
		Item* pile_of_sticks = new Misc("Stick pile", "Quite dry, would make good tinder.");
		Item* small_log = new Misc("Small Log", "Not as heavy as you'd expect, should burn fast.");
		Item* pebble = new Misc("pebble", "Small and smooth, would be good for skimming.");
		Item* pouch_of_pebbles = new Misc("Pouch of Pebbles", "Strange that there's a pouch in the woods?");
		Item* ferro_rod = new Misc("Flint and Steel", "Probably left behind by the campers.");
		Item* fishing_rod = new TestType("Fishing Rod", "OH HELL YEAH!");
		Item* powder_gun = new Weapon("Powder Gun", "Hmmmmmmmmmmm if only i had the powder");	// There's no powder ;)
		Item* bear_trap = new Misc("Bear Trap", "Snapping force could really hurt something...");
		Item* hunters_hide_set = new Armour("Hunters Hide Set", "Fits nice and snug, a good outdoor kit.");

		items.insert(std::pair<std::string, Item*>(silver_sword->getName(), silver_sword));
		items.insert(std::pair<std::string, Item*>(pile_of_sticks->getName(), pile_of_sticks));
		items.insert(std::pair<std::string, Item*>(small_log->getName(), small_log));
		items.insert(std::pair<std::string, Item*>(pebble->getName(), pebble));
		items.insert(std::pair<std::string, Item*>(pouch_of_pebbles->getName(), pouch_of_pebbles));
		items.insert(std::pair<std::string, Item*>(ferro_rod->getName(), ferro_rod));
		items.insert(std::pair<std::string, Item*>(fishing_rod->getName(), fishing_rod));
		items.insert(std::pair<std::string, Item*>(powder_gun->getName(), powder_gun));
		items.insert(std::pair<std::string, Item*>(bear_trap->getName(), bear_trap));
		items.insert(std::pair<std::string, Item*>(hunters_hide_set->getName(), hunters_hide_set));

		return items;
		}
	}
}

//	This is where we allocate memory for the rooms and push the pointers to the 
//	locations array to be passed to the gameplay state for use.
std::vector<Location*> AdventureSelectMenu::constructLocations
	(ADVENTURES current_adventure) {
	std::vector<Location*> locations = {};

	switch (current_adventure) {
	case DWARF_CAVERNS: {
		//	Allocate Memory
		Location* entrance = new Location();
		Location* great_hall = new Location();
		Location* throng_room = new Location();
		Location* throng_room_north_hall = new Location();
		Location* throng_room_west_hall = new Location();
		Location* crypt = new Location();
		Location* beer_room = new Location();
		Location* great_forge = new Location();

		//	Push pointers to locations
		locations.push_back(entrance);
		locations.push_back(great_hall);
		locations.push_back(throng_room);
		locations.push_back(throng_room_north_hall);
		locations.push_back(throng_room_west_hall);
		locations.push_back(crypt);
		locations.push_back(beer_room);
		locations.push_back(great_forge);

		return locations;
	}
	
	case ELVEN_CAPITAL: {
		Location* courtyard = new Location();
		Location* eastern_ascending_stairway = new Location();
		Location* western_ascending_stairway = new Location();
		Location* western_descending_stairway = new Location();
		Location* southern_descending_stairway = new Location();
		Location* gay_elven_gathering_area = new Location();
		Location* capitals_cultural_center = new Location();
		Location* big_tree_lookout = new Location();
		Location* city_gates = new Location();

		locations.push_back(courtyard);
		locations.push_back(eastern_ascending_stairway);
		locations.push_back(western_ascending_stairway);
		locations.push_back(western_descending_stairway);
		locations.push_back(southern_descending_stairway);
		locations.push_back(gay_elven_gathering_area);
		locations.push_back(capitals_cultural_center);
		locations.push_back(big_tree_lookout);
		locations.push_back(city_gates);

		return locations; }

	case NIGHTMARE_WOODS: {
		Location* path_a = new Location();
		Location* path_b = new Location();
		Location* path_b_clearing = new Location();
		Location* path_c = new Location();
		Location* path_d = new Location();
		Location* path_e = new Location();
		Location* path_e_camp_grounds = new Location();
		Location* path_f = new Location();
		Location* path_g = new Location();
		Location* path_g_lake = new Location();
		Location* path_h = new Location();
		Location* path_h_cabin = new Location();
		Location* path_i = new Location();

		locations.push_back(path_a);
		locations.push_back(path_b);
		locations.push_back(path_b_clearing);
		locations.push_back(path_c);
		locations.push_back(path_d);
		locations.push_back(path_e);
		locations.push_back(path_e_camp_grounds);
		locations.push_back(path_f);
		locations.push_back(path_g);
		locations.push_back(path_g_lake);
		locations.push_back(path_h);
		locations.push_back(path_h_cabin);
		locations.push_back(path_i);

		return locations;
		}
	}
}

void AdventureSelectMenu::loadLocationBase() {
	for (int location_idx = 0; 
		location_idx <= sizeof(_adventure_locations);
		location_idx++) {
		// Set name then description
		_adventure_locations[location_idx]->setName(_raw_world_data[location_idx][0]);
		_adventure_locations[location_idx]->setName(_raw_world_data[location_idx][1]);
	}
}

/*	Cycle through each location contained within the save file.
*	Check each locations saved item name data and if the saved name is in the worlds
*	items map then insert a copy to that room. */	

//	Might have to create a copy constructor for items to allow for multiple items in
//	a location.
void AdventureSelectMenu::loadLocationItems() {
	char delimiter = ',';
	int start_idx, end_idx;
	
	std::string raw_item_string;
	std::vector<std::string> item_names = {};
	Item* new_item = nullptr;


	for (int location_idx = 0; 
		location_idx < _adventure_locations.size(); 
		location_idx++) {
		
		start_idx = 0;
		end_idx = 0;
		raw_item_string = _raw_world_data[location_idx][2];

		// Assign each dir and exit name to an element in a vector
		for (int i = 0; i < raw_item_string.size(); i++) {
			if ((char)raw_item_string[i] == delimiter) {
				std::string delimited_data;
				end_idx = i;
				delimited_data.append(raw_item_string, start_idx, end_idx - start_idx);
				item_names.push_back(delimited_data);

				start_idx = end_idx + 1;
			}
		}

		// Using the item name lookup the item from the _world_items map and copy
		// that item to the location.
		for (auto item_name : item_names) {
			if (_world_items[item_name]) {
				if (typeid(_world_items[item_name]).name() == "8Weapon") {
					new_item = new Weapon(_world_items[item_name]->getName(),
						_world_items[item_name]->getDescription());
				}

				else if (typeid(_world_items[item_name]).name() == "8Armour") {
					new_item = new Armour(_world_items[item_name]->getName(),
						_world_items[item_name]->getDescription());
				}

				else if (typeid(_world_items[item_name]).name() == "8Consumable") {
					new_item = new Consumable(_world_items[item_name]->getName(),
						_world_items[item_name]->getDescription());
				}

				else if (typeid(_world_items[item_name]).name() == "8Misc") {
					new_item = new Misc(_world_items[item_name]->getName(),
						_world_items[item_name]->getDescription());
				}

				else if (typeid(_world_items[item_name]).name() == "8TestType") {
					new_item = new TestType(_world_items[item_name]->getName(),
						_world_items[item_name]->getDescription());
				}
			}

			if (new_item != nullptr) {
				_adventure_locations[location_idx]->addItem(item_name, new_item);
			}
		}

	}
}

//	Take the last element of the _world_data and process this around a delimiter
void AdventureSelectMenu::loadLocationExits() {
	char delimiter = ',';
	int start_idx, end_idx;
	
	std::string raw_exit_data;
	std::vector<std::string> formatted_exit_data = {};
	std::string extracted_dir;
	std::string extracted_exit_name;
	Location* extracted_exit_ptr;


	for (int location_idx = 0;
		location_idx < _adventure_locations.size();
		location_idx++) {

		start_idx = 0;
		end_idx = 0;
		raw_exit_data = _raw_world_data[location_idx][3];

		// Assign each dir and exit name to an element in a vector
		for (int i = 0; i < raw_exit_data.size(); i++) {
			if ((char)raw_exit_data[i] == delimiter) {
				std::string delimited_data;
				end_idx = i;
				delimited_data.append(raw_exit_data, start_idx, end_idx - start_idx);
				formatted_exit_data.push_back(delimited_data);

				start_idx = end_idx + 1;
			}
		}

		// We know there's only 2 possibilities for exits, the data can be a direction or 
		// location, additionally we know that the first element of the raw exit set data will
		// be a direction, therefore we can use the modulo operator to extract what we need and 
		// reference our set of locations for the correct pointer.
		for (int idx = 0; idx < formatted_exit_data.size(); idx++) {
			if(idx % 2 == 0) { extracted_dir = formatted_exit_data[idx]; }
			else { 
				extracted_exit_name = formatted_exit_data[idx]; 
				for(auto location : _adventure_locations){
					if (location->getName() == extracted_exit_name) { extracted_exit_ptr = location; }
				}
			}

			_adventure_locations[location_idx]->addExit(extracted_dir, extracted_exit_ptr);
		}
	}
}

void AdventureSelectMenu::setWorldLoader(WorldLoader* world_loader) { _world_loader = world_loader; }
std::vector<Location*> AdventureSelectMenu::returnLocationData() { return _adventure_locations; }

STATES AdventureSelectMenu::update() {
	std::string save_name;
	int choice;

	std::cin >> choice;
	std::cout << std::endl;

	// Do all of the work during adventure select as this will be passed
	// to the gameplay state once configured to save load times (if noticable).
	if (choice <= _num_worlds && choice > 0 ) {
		cacheSaveData(choice);
	
		// This only works if the adventure select display is in the same order as the 
		// ADVENTURES enum. Additionally...
		// This data has to be manipulated and then transformed into location parameters
		// before we can set the statemanagers version of world_data
		_world_items = constructItems(ADVENTURES(choice - 1));
		_adventure_locations = constructLocations(ADVENTURES(choice-1));
		
		loadLocationBase();
		loadLocationItems(); 
		loadLocationExits();
	}

	return STATES::GAMEPLAY;
}

void AdventureSelectMenu::render() {
	std::cout << std::endl << "Zork(ish) :: Select Adventure " << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << ">> 1. Dwarf Caverns" << std::endl;
	std::cout << ">> 2. Elven Capital" << std::endl;
	std::cout << ">> 3. Nightmare Woods" << std::endl;
	std::cout << ">> ";
}





//Help menu definitions
STATES HelpMenu::update() { return STATES::MAIN_MENU; }

void HelpMenu::render() {}






//Gameplay state definitions
GameplayState::GameplayState(std::vector<Location*> location_data) {
	if (!location_data.empty()) {
		_location_data = location_data;
		_current_location = location_data[0];
	}
}

STATES GameplayState::update() {
	std::string action;
	std::string object;

	std::cin >> action;
	std::cin >> object;
	std::cout << std::endl;

	// Using this big chunk of if-else statements until command processor is build
	if (action == "quit" && object == "game") { return STATES::QUIT; }
	else if (action == "show" && object == "highscores") { return STATES::VIEW_HoF; }
	else if (action == "show" && object == "inventory") {
		//_player.showInventory();
		return STATES::GAMEPLAY;
	}
	else { return STATES::GAMEPLAY; }
}

void GameplayState::render() {
	std::cout << std::endl;
	_current_location->showDetails();

	std::cout << "	- Allowed stage 1 commands can be found in the help screen" << std::endl;
	std::cout << "	- Please enter test commands" << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl << std::endl;
	std::cout << std::endl << ">> Action: ";
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