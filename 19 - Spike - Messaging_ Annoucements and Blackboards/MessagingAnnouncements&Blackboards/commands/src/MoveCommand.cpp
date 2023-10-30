#include "../hdr/MoveCommand.h"

MoveCommand::MoveCommand() {}

void MoveCommand::setData(GameData* game_data_frame, std::string exit_UEID) {
	if (_game_data == nullptr) { _game_data = game_data_frame; }
	_exit_UEID = exit_UEID; }

/* Expects the argument to contain only 1 element, the direction to move	*/
void MoveCommand::triggerEvent() {
	for (auto& renderer : _game_data->c_renderers) {
		//	if renderer belongs to current location
		if (renderer.second->getUCID().front() == _game_data->current_location.front()) {
			renderer.second->flagForRender(false);	}

		if (renderer.second->getUCID().front() == _exit_UEID.front()) {
			renderer.second->flagForRender(true); }
	}

	_game_data->current_location = _exit_UEID;
	_game_data->discovered_area = false;
	_game_data->reinstance_local_entity_cache = true; }