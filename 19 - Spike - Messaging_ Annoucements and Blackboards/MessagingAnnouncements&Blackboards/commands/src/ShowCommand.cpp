#include "../hdr/ShowCommand.h"

void ShowCommand::setData(GameData* game_data, std::string arg) { 
	if (_game_data == nullptr) { _game_data = game_data; }
	_modifier = arg; }

void ShowCommand::triggerEvent() {
	if (_modifier == "inventory") {
		std::string owners_id;

		for (C_Inventory* inventory : _game_data->_local_inventories) {
			owners_id = extractUEID(inventory->getUCID());

			if (owners_id.front() == _game_data->player.front()) {
				for (std::string item_id : inventory->held_item_UEIDs) {
					std::string item_renderer_id = item_id;
					item_renderer_id.append("A");

					_game_data->c_renderers[item_renderer_id]->flagForRender(true);
				}
			}
		}
	}
	else if (_modifier == "highscore") {
		// Do highscore stuffs
	}
}



std::string ShowCommand::extractUEID(std::string ucid) {
	// Check each character of the cuid until we hit an upper case letter
	// take all the characters from before the upper case and that's our EUID
	// to return.
	std::string::iterator ucid_it;
	std::string UEID;

	for (ucid_it = ucid.begin(); ucid_it != ucid.end(); ucid_it++) {
		if (char(*ucid_it) > 96 && char(*ucid_it) < 123) {
			std::string EUID_element(1, char(*ucid_it));
			UEID.append(EUID_element);
		}
		else { return UEID; }
	}

	return UEID;
}