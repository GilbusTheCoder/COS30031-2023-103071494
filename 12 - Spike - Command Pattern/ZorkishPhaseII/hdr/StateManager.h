#include <vector>
#include "WorldLoader.h"
#pragma once

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

/*	Ok so truth be told i really hate that setLocations is a virtual functions
*	really, i do, but it's the first thing i thought of so we'll roll with it
*	it's midnight btw...													*/
class State {
public:
	virtual STATES update() = 0;
	virtual void render() = 0;
	virtual void setLocations(std::vector<Location*> locations) = 0;
};


class MainMenu : public State {
public:
	STATES update() override;
	void render() override;
	void setLocations(std::vector<Location*> locations) override;
};

class AboutMenu : public State {
public:
	STATES update() override;
	void render() override;
	void setLocations(std::vector<Location*> locations) override;
};

class HelpMenu : public State {
public:
	STATES update() override;
	void render() override;
	void setLocations(std::vector<Location*> locations) override;
};

class AdventureSelectMenu : public State {
private:
	WorldLoader* _world_loader;
	std::vector<Location*> _locations;

public:
	AdventureSelectMenu();
	~AdventureSelectMenu();

	void deleteLoader();
	std::vector<Location*> getLocations();

	STATES update() override;
	void render() override;
	void setLocations(std::vector<Location*> locations) override;
};

class GameplayState : public State {
private:
	std::vector<Location*> _locations;
public:
	~GameplayState();

	STATES update() override;
	void render() override;
	void setLocations(std::vector<Location*> locations) override;
};

class NewHighScoreMenu : public State {
public:
	STATES update() override;
	void render() override;
	void setLocations(std::vector<Location*> locations) override;
};

class HallOfFameMenu : public State {
public:
	STATES update() override;
	void render() override;
	void setLocations(std::vector<Location*> locations) override;
};

class QuitState : public State {
public:
	STATES update() override;
	void render() override;
	void setLocations(std::vector<Location*> locations) override;
};

class StateManager {
private:
	MainMenu _main_menu;
	AboutMenu _about_menu;
	HelpMenu _help_menu;
	AdventureSelectMenu _adventure_select_menu;
	GameplayState _gameplay;
	NewHighScoreMenu _new_hs_menu;
	HallOfFameMenu _hall_of_fame_menu;
	QuitState _quit;

	State* _current_ptr = &_main_menu;
	STATES _current_state = STATES::MAIN_MENU;


public:
	StateManager();
	bool isRunning();
	void update();
	void render();
};