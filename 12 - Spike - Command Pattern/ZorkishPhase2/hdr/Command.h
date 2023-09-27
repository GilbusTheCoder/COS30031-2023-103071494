#pragma once
#include "GameData.h"
class Command {
public:
	virtual void execute(GameData* game_data, std::vector<std::string> args) = 0;
};

// The direction is the first and only argument contained in args
class MoveCommand : public Command {
public:
	void execute(GameData* game_data, std::vector<std::string> args) override;
};

// Take command
class TakeCommand : public Command {
public:
	void execute(GameData* game_data, std::vector<std::string> args) override;

private:
	std::string determineItemName(std::vector<std::string>& args);
	bool isItemEnclosed(const std::vector<std::string>& args);
};

//	Drop command removes item from inventory and adds it to world
class DropCommand : public Command {
public:
	void execute(GameData* game_data, std::vector<std::string> args) override;

private:
	std::string determineItemName(std::vector<std::string>& args);
};

class LookCommand : public Command {
public:
	void execute(GameData * game_data, std::vector<std::string> args) override;

private:
	std::string determineItemName(std::vector<std::string>& args);
};



//	Used for menu interaction and instantiation, where-as look is a game command
class ShowCommand : public Command {
public:
	void execute(GameData* game_data, std::vector<std::string> args) override;

private:
	void showHelp();
};

class QuitCommand : public Command {
	void execute(GameData* game_data, std::vector<std::string> args) override;
};