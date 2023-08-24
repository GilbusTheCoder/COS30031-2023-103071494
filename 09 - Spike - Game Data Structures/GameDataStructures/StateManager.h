#pragma once
#include "player.h"

enum STATES {
	WELCOME,
	MAIN_MENU,
	ABOUT,
	HELP,
	SELECT_ADVENTURE,
	GAMEPLAY,
	NEW_HS,				//New Highscore
	VIEW_HoF,			//View Hall of Fame
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
public:
	STATES update() override;
	void render() override;
};

class GameplayState : public State {
private:

	// These items will most likely be stored in a map of somekind holding
	// both the item and address to it for reference so this isn't filthy and clogged.
	// For now this works to get the point across.
	InventoryItem _sword_of_testing = InventoryItem("Sword of Testing", "testType", "Better than the testing stick that's for sure.");
	InventoryItem _bundle_of_twigs = InventoryItem("Twigs", "fuel", "Common in the forest");
	InventoryItem _petrol_and_lighter = InventoryItem("Petrol and Lighter", "pestControl", "Don't like the forest? Don't have too ;)");
	InventoryItem* _sword_of_testing_ptr = &_sword_of_testing;
	InventoryItem* _bundle_of_twigs_ptr = &_bundle_of_twigs;
	InventoryItem* _petrol_and_lighter_ptr = &_petrol_and_lighter;

	InventorySlot _init_slot = InventorySlot(&_sword_of_testing);
	Player _player = Player(&_init_slot);

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

class StateManager
{
private:
	MainMenu _main_menu;
	AboutMenu _about_menu;
	HelpMenu _help_menu;
	AdventureSelectMenu _adventure_select_menu;
	GameplayState _gameplay;
	NewHighScoreMenu _new_highscore_menu;
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