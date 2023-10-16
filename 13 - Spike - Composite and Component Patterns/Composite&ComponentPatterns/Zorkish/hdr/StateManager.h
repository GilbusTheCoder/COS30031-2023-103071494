#include "States.h"

#pragma once
class StateManager
{
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
	STATES _current_state = STATES::S_MAIN_MENU;

public:
	StateManager();

	bool isRunning();
	void update();
	void render();
};