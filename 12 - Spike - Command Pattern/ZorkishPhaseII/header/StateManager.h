#pragma once
#include "../header/States.h"
#include "../header/WorldLoader.h"

class StateManager {
private:
	WorldLoader* _world_loader;

	MainMenu _main_menu;
	AboutMenu _about_menu;
	HelpMenu _help_menu;
	AdventureSelectMenu _adventure_select_menu;
	GameplayState _gameplay = GameplayState(_location_data);
	NewHighScoreMenu _new_highscore_menu;
	HallOfFameMenu _hall_of_fame_menu;
	QuitState _quit;

	bool _has_loaded_save_game = false;
	std::vector<Location*> _location_data;
	STATES _current_state = STATES::MAIN_MENU;
	State* _current_ptr = &_main_menu;


public:
	StateManager();
	bool isRunning();
	
	void update();
	void render();
};
