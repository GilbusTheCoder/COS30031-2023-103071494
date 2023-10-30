#include <algorithm>
#include "../hdr/InputHandler.h"

/******************************************************************************
*							    De/Constructors
******************************************************************************/
InputHandler::InputHandler(InputData* input_data) {
	if (input_data != nullptr) { _input_data = input_data; }
	else { _input_data = new InputData; }
}

InputHandler::~InputHandler() {
	if (_input_data != nullptr) {
		delete _input_data;
		_input_data = nullptr; }
}



InputData* InputHandler::handleInput(std::stringstream& entered_data, GameData* game_data) {
	std::vector<std::string> raw_args;
	resetInputData();

	while (entered_data.good()) {
		std::string command_arg;
		entered_data >> command_arg;
		raw_args.emplace_back(command_arg);
	}

	for (std::string& arg : raw_args) {
		std::transform(arg.begin(), arg.end(), arg.begin(), std::tolower); }

	std::string raw_c_type = raw_args[0];
	_input_data->c_type = validateCommandType(raw_args[0]);
	raw_args.erase(raw_args.begin());
	raw_args.shrink_to_fit();

	_input_data->args = formatArgsForType(raw_c_type, raw_args, game_data);
	return _input_data;
}

void InputHandler::resetInputData() {
	_input_data->c_type = CommandType::INVALID;
	_input_data->args.clear();
	_input_data->args.shrink_to_fit();
}

CommandType InputHandler::validateCommandType(std::string raw_c_type) {
	if (!raw_c_type.empty()) {
		std::transform(raw_c_type.begin(), raw_c_type.end(), raw_c_type.begin(), std::tolower);
	}
	//	Instantiating aliases is just refactoring this piece of code here to read from a map
	//	containing a valid command and a string of aliases which can be added to, just got to
	//	check for command collisions when adding.
	if (raw_c_type == "move" || raw_c_type == "head" || raw_c_type == "go" ||
		raw_c_type == "m" || raw_c_type == "g") {
		return CommandType::MOVE;
	}
	else if (raw_c_type == "take" || raw_c_type == "grab" || raw_c_type == "t" ||
		raw_c_type == "drop" || raw_c_type == "d" || raw_c_type == "discard") {
		return CommandType::TAKE; }
	else if (raw_c_type == "look" || raw_c_type == "l") {
		return CommandType::LOOK; }
	else if (raw_c_type == "show" || raw_c_type == "sh" || raw_c_type == "s") {
		return CommandType::SHOW; }
	else if (raw_c_type == "quit" || raw_c_type == "q") {
		return CommandType::QUIT; }
	else { return CommandType::INVALID; }
}

std::vector<std::string> InputHandler::formatArgsForType(std::string raw_c_type,
	std::vector<std::string> args, GameData* game_data) {
	std::vector<std::string> fmt_args;

	// Spit out the formatted args for whatever command type
	switch (_input_data->c_type) {
	case CommandType::LOOK: {
		if (args.size() > 1) {
			std::string modifier = args[0];
			std::string item_name = getItemName(args);

			fmt_args.emplace_back(modifier);
			fmt_args.emplace_back(item_name);
		}
		else if (args.size() == 1) {
			std::string modifier = "around";
			fmt_args.emplace_back(modifier);
		} return fmt_args;

		// Format item name and figure out src address and dest address
		// For now only care about player and current location interactions
	case CommandType::TAKE: {
		raw_c_type = formatTakeOrDrop(raw_c_type);

		std::string src_UCID = game_data->
			_local_inventories[takeOrDrop(raw_c_type)]->getUCID();
		std::string dest_UCID = game_data->
			_local_inventories[!takeOrDrop(raw_c_type)]->getUCID();
		std::string item_name = getItemName(args);

		_input_data->src = game_data->c_inventories[src_UCID];
		_input_data->dest = game_data->c_inventories[dest_UCID];

		for (C_Render* renderer : game_data->_local_renderers) {
			if (renderer->getName() == item_name){
				args.clear();
				args.shrink_to_fit();
				std::string item_id = extractUEID(renderer->getUCID());
				_input_data->item = game_data->entities[item_id];
				return args;
			}
		}
		
		break;
	}

	default:
		return args; }

	}

	return args;
}

// Expects raw message format as given by user input - c_type;
std::string InputHandler::getItemName(std::vector<std::string> args, 
	std::string safety_word) {
	std::string item_name;
	std::vector<std::string> c_args = args;
	std::vector<std::string>::iterator args_it;

	if (c_args.size() > 0) {
		if (c_args[0] == "at") {
			//	Start at element 2 as first arg should be "at"
			for (args_it = c_args.begin() + 1; args_it != c_args.end(); ++args_it) {
				if (*args_it == safety_word) {
					item_name.pop_back();
					return item_name; }

				std::string arg = *args_it;
				arg.append(" ");
				item_name.append(arg);
			}

			if (!item_name.empty()) { item_name.pop_back(); }
		} else {	//	Assume item name is the args passed
			for (args_it = c_args.begin(); args_it != c_args.end(); ++args_it) {
				if (*args_it == safety_word) {
					item_name.pop_back();
					return item_name;
				}

				std::string name_part = *args_it;
				name_part.append(" ");
				item_name.append(name_part);
			}

		}
	}

	if (item_name.back() == ' ') { item_name.pop_back(); }
	return item_name;
}

bool InputHandler::takeOrDrop(std::string take_modifier) {
	if (take_modifier == "take") { return true; }
	return false; }

std::string InputHandler::formatTakeOrDrop(std::string raw_c_arg) {
	std::string raw_arg;
	
	if (raw_c_arg == "take" || raw_c_arg == "grab" || raw_c_arg == "t") {
		raw_arg = "take";} 
	else if (raw_c_arg == "drop" || raw_c_arg == "d" || raw_c_arg == "discard") {
		raw_arg = "drop"; }

	return raw_arg;
}

std::string InputHandler::extractUEID(std::string ucid) {
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
