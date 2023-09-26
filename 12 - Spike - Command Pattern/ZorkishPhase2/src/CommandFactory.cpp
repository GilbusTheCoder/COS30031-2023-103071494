#include "../hdr/CommandFactory.h"

std::queue<Command*> CommandFactory::createCommands(std::string c_type,
	std::vector<std::string> c_args) {
	std::queue<Command*> commands;
	
	if (c_type == "move" && c_args.size() == 1) {
		commands.push(new MoveCommand());
	}

	return commands;
}