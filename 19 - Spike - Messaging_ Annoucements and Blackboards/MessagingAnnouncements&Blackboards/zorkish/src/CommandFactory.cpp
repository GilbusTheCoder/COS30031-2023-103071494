#include "../hdr/CommandFactory.h"

std::queue<Command*> CommandFactory::createCommands(GameData* game_data,
	CommandType c_type, std::vector<std::string> c_args) {
	std::queue<Command*> commands;
	if (c_type == CommandType::MOVE) { commands.push(new MoveCommand(game_data, c_args)); }
	else if (c_type == CommandType::TAKE) { commands.push(new TakeCommand(game_data, c_args)); }
	else if (c_type == CommandType::DROP) { commands.push(new DropCommand(game_data, c_args)); }
	else if (c_type == CommandType::LOOK) { commands.push(new LookCommand(game_data, c_args)); }
	else if (c_type == CommandType::SHOW) { commands.push(new ShowCommand(game_data, c_args)); }
	else if (c_type == CommandType::QUIT) { commands.push(new QuitCommand(game_data)); }

	return commands;
}
