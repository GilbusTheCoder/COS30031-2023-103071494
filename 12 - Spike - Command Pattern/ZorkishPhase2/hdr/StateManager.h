#pragma once
#include <vector>
#include "States.h"

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

	GameData* _game_data = nullptr;
	State* _current_ptr = &_main_menu;
	STATES _current_state = STATES::MAIN_MENU;


public:
	StateManager();
	GameplayState* getGameplayState();

	bool isRunning();
	void update();
	void render();
};