#include <sstream>
#include "InputData.h"

#pragma once 
class InputHandler {
private:
	InputData* _input_data = nullptr;

public:
	InputHandler(InputData* input_data = nullptr);
	~InputHandler();

	InputData* handleInput(std::stringstream input_data);

private:
	void resetInputData();
	CommandType validateCommandType(std::string raw_c_type);

};

