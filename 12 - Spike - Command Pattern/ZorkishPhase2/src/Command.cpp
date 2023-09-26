#include "../hdr/Command.h"

// Currently breaks on bad input, don't worry though it isn't up to the command
// to validate input.
void MoveCommand::execute(GameData* game_data, std::vector<std::string> args) {
	game_data->current_location = game_data->current_location->getExit(args[0]);
}