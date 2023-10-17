#include "GameData.h"

#pragma once
enum CommandType {
	INVALID,
	MOVE,	// go somewhere
	TAKE,	// take item
	DROP,	// drop item or component if removable
	LOOK,	// display surrounding renderer info
	SHOW,	// display attached component info
	HELP,	// render the help entity
	QUIT,	// change game_data is_running to false
};

class Command {
protected:
	GameData* __game_data = nullptr;
	std::vector<std::string> __args;

	std::string UEIDFromRenderName(std::string entity_rendered_name);
	std::string extractUEID(std::string UCID);

public:
	virtual void execute() = 0;
};

class MoveCommand : virtual public Command {
public:
	MoveCommand(GameData* game_data, std::vector<std::string> args);
	void execute() override;
};

class TakeCommand : virtual public Command {
private:
	std::vector<std::string> formatArgs(std::vector<std::string> raw_args);

public:
	TakeCommand(GameData* game_data, std::vector<std::string> args);
	void execute() override;
};

class DropCommand : virtual public Command {
private:
	std::vector<std::string> formatArgs(std::vector<std::string> raw_args);

public:
	DropCommand(GameData* game_data, std::vector<std::string> args);
	void execute() override;
};

class LookCommand : virtual public Command {
private:
	std::vector<std::string> _allowed_modifiers = {
		"around",
		"at",
		"in"
	};

	std::vector<std::string> formatArgs(std::vector<std::string> raw_args);

public:
	LookCommand(GameData* game_data, std::vector<std::string> args);
	void execute() override;
};

class ShowCommand : virtual public Command {
public:
	ShowCommand(GameData* game_data, std::vector<std::string> args);
	void execute() override;
};

class QuitCommand : virtual public Command {
public:
	QuitCommand(GameData* game_data);
	void execute() override;
};