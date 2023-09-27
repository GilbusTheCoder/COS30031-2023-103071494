#include "../hdr/CommandFactory.h"

std::queue<Command*> CommandFactory::createCommands(std::string c_type,
	std::vector<std::string> c_args) {
	std::queue<Command*> commands;
	
	if (c_type == "move") { commands.push(new MoveCommand()); }
	else if (c_type == "take") { commands.push(new TakeCommand()); }
	else if (c_type == "drop") { commands.push(new DropCommand()); }
	else if (c_type == "look") { commands.push(new LookCommand()); }
	else if (c_type == "show") { commands.push(new ShowCommand()); }
	else if (c_type == "quit") { commands.push(new QuitCommand()); }

	return commands;
}