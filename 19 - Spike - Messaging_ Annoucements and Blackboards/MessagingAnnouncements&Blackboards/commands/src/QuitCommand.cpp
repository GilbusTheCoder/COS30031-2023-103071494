#include "../hdr/QuitCommand.h"

QuitCommand::QuitCommand() {}

void QuitCommand::setData(GameData* game_data_frame) {
	if (_game_data == nullptr) { _game_data = game_data_frame; } }

void QuitCommand::triggerEvent() { _game_data->is_running = false; }
