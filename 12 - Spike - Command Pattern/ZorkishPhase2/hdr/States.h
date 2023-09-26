#pragma once
#include <iostream>
#include <vector>
#include "WorldLoader.h"

enum STATES {
	WELCOME,
	MAIN_MENU,
	ABOUT,
	HELP,
	SELECT_ADVENTURE,
	GAMEPLAY,
	NEW_HS,		//New Highscore
	VIEW_HoF,	//View Hall of Fame
	QUIT,
};

/*	Ok so truth be told i really hate that setStateData is a virtual functions
*	really, i do, but it's the first thing i thought of so we'll roll with it
*	it's midnight btw...													*/
class State {

public:
    GameData* game_data = nullptr;
	virtual STATES update() = 0;
	virtual void render() = 0;
};


class MainMenu : public State {
public:
	STATES update() override;
	void render() override;
};

class AboutMenu : public State {
public:
	STATES update() override;
	void render() override;
};

class HelpMenu : public State {
public:
	STATES update() override;
	void render() override;
};

class AdventureSelectMenu : public State {
private:
	WorldLoader* _world_loader = nullptr;

public:
	AdventureSelectMenu();
	~AdventureSelectMenu();
	void deleteLoader();

	STATES update() override;
	void render() override;
};

//Create a data structure containing whatever the command needs to work.
class GameplayState : public State {
private:
	//CommandFactory* _command_factory = nullptr;
	std::string _command_type;
	std::vector<std::string> _command_args;

public:
	GameplayState();
	~GameplayState();

	std::stringstream getInput();
	void handleInput();
	void resetCommandData();

	STATES update() override;
	void render() override;
};

class NewHighScoreMenu : public State {
public:
	STATES update() override;
	void render() override;
};

class HallOfFameMenu : public State {
public:
	STATES update() override;
	void render() override;
};

class QuitState : public State {
public:
	STATES update() override;
	void render() override;
};


