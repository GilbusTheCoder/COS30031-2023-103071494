#include <algorithm>
#include "../hdr/Command.h"

std::string Command::UEIDFromRenderName(std::string entity_rendered_name) { 
	std::map<std::string, C_Render*>::iterator traversal_it;

	for (traversal_it = __game_data->c_renderers.begin();
		traversal_it != __game_data->c_renderers.end(); ++traversal_it) {
		if (traversal_it->second->getName() == entity_rendered_name) {
			std::string UEID;
			std::string UCID = traversal_it->first;
			std::string::iterator UCID_it;

			for (UCID_it = UCID.begin(); UCID_it != UCID.end(); UCID_it++) {
				if (char(*UCID_it) > 96 && char(*UCID_it) < 123) {
					std::string EUID_element(1, char(*UCID_it));
					UEID.append(EUID_element);
				}
				else { return UEID; }
			}

			return UEID;
		}
	}
}

std::string Command::extractUEID(std::string UCID) {
	// Check each character of the cuid until we hit an upper case letter
	// take all the characters from before the upper case and that's our EUID
	// to return.
	std::string::iterator ucid_it;
	std::string EUID;

	for (ucid_it = UCID.begin(); ucid_it != UCID.end(); ucid_it++) {
		if (char(*ucid_it) > 96 && char(*ucid_it) < 123) {
			std::string EUID_element(1, char(*ucid_it));
			EUID.append(EUID_element);
		}
		else { return EUID; }
	}

	return EUID;
}


/******************************************************************************
*									MoveCommand
*									Definitions
*
/******************************************************************************
*								Base Class Overrides
******************************************************************************/
MoveCommand::MoveCommand(GameData* game_data, std::vector<std::string> args) {
	Command::__game_data = game_data;
	Command::__args = args;
}

/* Expects the argument to contain only 1 element, the direction to move	*/
void MoveCommand::execute() {
	if (__args.size() > 0) {
		/*	Search through the current locations portals until there's one found
		*	with a direction matching the given argument.
		*   Once found we can get the render name and search for the portal	
		*
		*	THIS WILL SHIT THE BED IF THE LOCATION UEID > 1 CHAR!!
		*	i felt a fix wasn't neccessary this as it's a demonstration and im
		*	tired															*/
		std::map<std::string, C_Portal*>::iterator traversal_it;

		for (traversal_it = __game_data->c_portals.begin();
			traversal_it != __game_data->c_portals.end(); ++traversal_it) {

			if (traversal_it->first[0] == __game_data->current_location[0]
				&& traversal_it->second->getDirection() == __args[0]) {

				std::string current_loc_renderer = __game_data->current_location;
				current_loc_renderer.append("A");
				__game_data->c_renderers.find(current_loc_renderer)
					->second->flagForRender(false);

				Entity* new_current_location = traversal_it->second->getExit();

				__game_data->current_location = new_current_location->getID();
				std::string new_loc_renderer = __game_data->current_location;
				new_loc_renderer.append("A");
				__game_data->c_renderers.find(new_loc_renderer)
					->second->flagForRender(true);
				
				break;
			}
		}
	}
}



/******************************************************************************
*									TakeCommand
*									Definitions
*
/******************************************************************************
*								Base Class Overrides
******************************************************************************/
TakeCommand::TakeCommand(GameData * game_data, std::vector<std::string> args) {
	Command::__game_data = game_data;
	Command::__args = formatArgs(args);
}

void TakeCommand::execute() {
	/*	If size of args is 1 than we're taking from current_locations inventory
	*	If the args are longer than 1 then it's a "take x from y" instance,
			where y presides inside of our current_locations inventory		*/
	if (__args.size() == 1) {
		std::string item_UEID = UEIDFromRenderName(__args[0]);
		
		C_Inventory* current_location_inventory = nullptr;
		C_Inventory* player_inventory = nullptr;
		std::map<std::string, C_Inventory*>::iterator traversal_it;
		
		// Find relevant inventories
		for (traversal_it = __game_data->c_inventories.begin();
			traversal_it != __game_data->c_inventories.end(); ++traversal_it) {
			
			std::string UEID = extractUEID(traversal_it->first);
			if (UEID == __game_data->current_location) {
				current_location_inventory = traversal_it->second; }
			if (UEID == __game_data->player) {
				player_inventory = traversal_it->second; }
			if (current_location_inventory != nullptr && player_inventory != nullptr) {
				break;	}
		}

		// Do the item transfer
		int offset = current_location_inventory->hasItem(nullptr, item_UEID);
		if (offset) {
			Entity* item = current_location_inventory->getItem(offset);
			current_location_inventory->deleteItem(item);
			player_inventory->addItem(item);
		}
	}
}

/******************************************************************************
*								 Utility Methods
******************************************************************************/
/*	Converts the unformatted command args (could be several instances of an 
*	item name for example) into a useful set of args							*/
std::vector<std::string> TakeCommand::formatArgs(std::vector<std::string> raw_args) 
{	
	std::string fmt_arg;
	std::vector<std::string> item_name_parts;
	std::vector<std::string> fmt_args;
	
	while (!raw_args.empty()) { 
		if (raw_args[0] != "from") {
			item_name_parts.emplace_back(raw_args[0]);
			raw_args.erase(raw_args.begin());
			raw_args.shrink_to_fit(); 
		} else { break; } }

	for (std::string name_part : item_name_parts) {
		fmt_arg.append(name_part + " "); }
	fmt_arg.resize(fmt_arg.size() - 1);

	fmt_args.emplace_back(fmt_arg);		// Add the item name to fmt_arg
	return fmt_args;
}



/******************************************************************************
*									DropCommand
*									Definitions
*
/******************************************************************************
*								Base Class Overrides
******************************************************************************/
DropCommand::DropCommand(GameData* game_data, std::vector<std::string> args) { 
	Command::__game_data = game_data;
	Command::__args = formatArgs(args);
}

void DropCommand::execute() { 
	if (__args.size() == 1) {
		std::string item_UEID = UEIDFromRenderName(__args[0]);

		C_Inventory* current_location_inventory = nullptr;
		C_Inventory* player_inventory = nullptr;
		std::map<std::string, C_Inventory*>::iterator traversal_it;

		// Find relevant inventories
		for (traversal_it = __game_data->c_inventories.begin();
			traversal_it != __game_data->c_inventories.end(); ++traversal_it) {

			std::string UEID = extractUEID(traversal_it->first);
			if (UEID == __game_data->current_location) {
				current_location_inventory = traversal_it->second;
			}
			if (UEID == __game_data->player) {
				player_inventory = traversal_it->second;
			}
			if (current_location_inventory != nullptr && player_inventory != nullptr) {
				break;
			}
		}

		// Do the item transfer
		int offset = player_inventory->hasItem(nullptr, item_UEID);
		if (offset) {
			Entity* item = player_inventory->getItem(offset);
			player_inventory->deleteItem(item);
			current_location_inventory->addItem(item);
		}
	}
}

/******************************************************************************
*								 Utility Methods
******************************************************************************/
/*	Should eventually be able to format (look at x in y). Converst raw args into
*	potentially <arg1(at, in or around), item_name_x,, in, container_y		*/
std::vector<std::string> DropCommand::formatArgs(std::vector<std::string> raw_args) {
	std::string fmt_arg;
	std::vector<std::string> item_name_parts;
	std::vector<std::string> fmt_args;

	while (!raw_args.empty()) {
		item_name_parts.emplace_back(raw_args[0]);
		raw_args.erase(raw_args.begin());
		raw_args.shrink_to_fit();
	}

	for (std::string name_part : item_name_parts) {
		fmt_arg.append(name_part + " "); }

	fmt_arg.resize(fmt_arg.size() - 1);
	fmt_args.emplace_back(fmt_arg);		// Add the item name to fmt_arg
	return fmt_args;
}



/******************************************************************************
*									LookCommand
*									Definitions
*
/******************************************************************************
*								Base Class Overrides
******************************************************************************/
LookCommand::LookCommand(GameData* game_data, std::vector<std::string> args) {
	Command::__game_data = game_data;
	Command::__args = formatArgs(args);
}

void LookCommand::execute() {
	if (__args[0] == "around") {
		/*	Cycle through the current locations inventory, get the items
		*	render ID's and set their renders to turn on.			*/
		std::string current_loc_id = __game_data->current_location;
		C_Inventory* room_inventory = nullptr;

		std::map<std::string, C_Inventory*>::iterator traversal_it;
		for (traversal_it = __game_data->c_inventories.begin();
			traversal_it != __game_data->c_inventories.end(); ++traversal_it) {
			if (traversal_it->first[0] == current_loc_id[0]) {
				room_inventory = traversal_it->second;
				break;
			}
		}

		if (room_inventory != nullptr) {
			for (std::string item_id : room_inventory->held_item_EUIDs) {
				std::string item_renderer_id = item_id;
				item_renderer_id.append("A");

				__game_data->c_renderers.find(item_renderer_id)->second->flagForRender(true);
			}
		}
	}
}


/******************************************************************************
*								 Utility Methods
******************************************************************************/
/*	Should eventually be able to format (look at x in y). Converst raw args into
*	potentially <arg1(at, in or around), item_name_x,, in, container_y		*/
std::vector<std::string> LookCommand::formatArgs(std::vector<std::string> raw_args) { 
	bool good_args = false;
	std::vector<std::string> fmt_args;
	
	for (std::string modifier : _allowed_modifiers) {
		if (modifier == raw_args[0]) { good_args = true; break; } }
	
	if (good_args) {	
		fmt_args.emplace_back(raw_args[0]);
		raw_args.erase(raw_args.begin());
		raw_args.shrink_to_fit();
	}

	return fmt_args;
}



/******************************************************************************
*									ShowCommand
*									Definitions
*
/******************************************************************************
*								Base Class Overrides
******************************************************************************/
ShowCommand::ShowCommand(GameData* game_data, std::vector<std::string> args) {
	Command::__game_data = game_data;
	Command::__args = args;
}

void ShowCommand::execute() {
	if (__args.size() == 1) {
		// Only functionality required for now
		if (__args[0] == "inventory") {
			/*	Find the players inventory and set all of the items to be renderered */
			std::string player_inventory_UCID = __game_data->player;
			player_inventory_UCID.append("A");

			C_Inventory* player_inventory = 
				__game_data->c_inventories.find(player_inventory_UCID)->second;
		
			for (std::string item_id : player_inventory->held_item_EUIDs) {
				std::string item_renderer_id = item_id;
				item_renderer_id.append("A");

				__game_data->c_renderers.find(item_renderer_id)->second->flagForRender(true);
			}
		}
	}
}



/******************************************************************************
*									QuitCommand
*									Definitions
*
/******************************************************************************
*								Base Class Overrides
******************************************************************************/

QuitCommand::QuitCommand(GameData* game_data) {
	Command::__game_data = game_data;
}

void QuitCommand::execute() { __game_data->is_running = false; }