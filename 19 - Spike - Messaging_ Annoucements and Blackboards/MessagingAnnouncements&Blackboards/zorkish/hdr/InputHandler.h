#include <sstream>
#include "InputData.h"

#pragma once 
class InputHandler {
private:
	InputData* _input_data = nullptr;

public:
	InputHandler(InputData* input_data = nullptr);
	~InputHandler();

	InputData* handleInput(std::stringstream& raw_input, GameData* game_data);

private:
	void resetInputData();
	CommandType validateCommandType(std::string raw_c_type);

	std::vector<std::string> formatArgsForType(std::string raw_c_type,
		std::vector<std::string> args, GameData* game_data);

	std::string getItemName(std::vector<std::string> args, std::string safety_word = "");
	bool takeOrDrop(std::string take_modifier);
	std::string formatTakeOrDrop(std::string raw_c_arg);
	std::string extractUEID(std::string ucid);
};

