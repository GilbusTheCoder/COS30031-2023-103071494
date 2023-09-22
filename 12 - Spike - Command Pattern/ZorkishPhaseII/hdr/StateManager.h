#include <vector>
#include "Location.h"
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

class State {
public:
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
	std::vector<Location*> _locations;
	void constructLocations(int num_locations);

public:
	AdventureSelectMenu(int num_locations = 0);
	STATES update() override;
	void render() override;
};

class GameplayState : public State {
public:
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