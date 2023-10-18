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



InputData* InputHandler::handleInput(std::stringstream input_data) {
	std::vector<std::string> raw_args;
	resetInputData();

	while (input_data.good()) {
		std::string command_arg;
		input_data >> command_arg;
		raw_args.emplace_back(command_arg);
	}

	for (std::string& arg : raw_args) {
		std::transform(arg.begin(), arg.end(), arg.begin(), std::tolower); }

	_input_data->c_type = validateCommandType(raw_args[0]);
	raw_args.erase(raw_args.begin());
	raw_args.shrink_to_fit();

	_input_data->_args = raw_args;

	return _input_data;
}

void InputHandler::resetInputData() {
	_input_data->c_type = CommandType::INVALID;
	_input_data->_args.clear();
	_input_data->_args.shrink_to_fit();
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
		return CommandType::MOVE; }
	else if (raw_c_type == "take" || raw_c_type == "grab" || raw_c_type == "t") {
		return CommandType::TAKE; }
	else if (raw_c_type == "look" || raw_c_type == "l") {
		return CommandType::LOOK; }
	else if (raw_c_type == "show" || raw_c_type == "sh" || raw_c_type == "s") {
		return CommandType::SHOW; }
	else if (raw_c_type == "quit" || raw_c_type == "q") {
		return CommandType::QUIT; }
	else { return CommandType::INVALID; }
}
