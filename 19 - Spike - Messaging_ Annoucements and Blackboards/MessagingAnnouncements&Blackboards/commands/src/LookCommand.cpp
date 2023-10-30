#include "../hdr/LookCommand.h"

void LookCommand::setData(GameData* game_data, InputData* input_data) {
	if (_game_data == nullptr) { _game_data = game_data; }
	_input_data = input_data; }

void LookCommand::triggerEvent() {
	LookTriggerType look_trigger = determineTriggerType();

	switch (look_trigger) {
	case LookTriggerType::LOOK_ALL:
		lookAtAll();
		break;

	case LookTriggerType::LOOK_SPECIFIC:
		lookAtSpecific();
		break;

	case LookTriggerType::LOOK_CONTAINER:
		break;

	default:
		break;
	}
}


LookTriggerType LookCommand::determineTriggerType() {	
	if (_input_data->args[0] == "around") { 
		return LookTriggerType::LOOK_ALL; }
	else if (_input_data->args[0] == "at") { 
		return LookTriggerType::LOOK_SPECIFIC; }
	// Command chaining isn't implemented in this spike
	else if (_input_data->args[0] == "in") { 
		return LookTriggerType::LOOK_CONTAINER; }
	else { return LookTriggerType::LOOK_INVALID; }
}

void LookCommand::lookAtAll() { 
	for (C_Render* renderer : _game_data->_local_renderers) {
		std::string UEID = extractUEID(renderer->getUCID());

		renderer->flagForRender(true);
		if (UEID.front() == _game_data->current_location.front()) {
			renderer->flagForRender(false);
			renderer->doShallowRender(false);
		}
	}
}

void LookCommand::lookAtSpecific() {
	for (C_Render* renderer : _game_data->_local_renderers) {
		if (renderer->getName() == _input_data->args[1]) {
			renderer->flagForRender(true);
			renderer->doShallowRender(false);
		}
	}
}

void LookCommand::lookAtContainer() { }

std::string LookCommand::extractUEID(std::string cuid) {
	// Check each character of the cuid until we hit an upper case letter
	// take all the characters from before the upper case and that's our EUID
	// to return.
	std::string::iterator cuid_it;
	std::string EUID;

	for (cuid_it = cuid.begin(); cuid_it != cuid.end(); cuid_it++) {
		if (char(*cuid_it) > 96 && char(*cuid_it) < 123) {
			std::string EUID_element(1, char(*cuid_it));
			EUID.append(EUID_element);
		}
		else { return EUID; }
	}

	return EUID;
}