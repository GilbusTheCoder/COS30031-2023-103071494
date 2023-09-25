#include "../hdr/Command.h"

/*	The args here will include only 1 string containing the direction of the 
*	exit we're aiming to move through									  */
void MoveCommand::execute(GameData* game_data, std::vector<std::string> args) {
	game_data->current_location = game_data->current_location->getExit(args[0]);
}