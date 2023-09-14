#pragma once
#include "player.h"
#include "StateManager.h"
#include "Location.h"

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

enum ADVENTURES {
	DWARF_CAVERNS,
	ELVEN_CAPITAL,
	NIGHTMARE_WOODS
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

// The adventure select menu is used to load world data from a file.
// It will then pass this world data to the gameplay State to use.

// It's also ok that this code is gross and slow. That's why it's called 'loading'.
// at least that's how im thinking about it.
class AdventureSelectMenu : public State {
private:
	int _num_worlds = 3;
	
	WorldLoader* _world_loader = new WorldLoader();
	std::vector<std::vector<std::string>> _raw_world_data;
	std::unordered_map<std::string, Item*> _world_items;
	std::vector<Location*> _adventure_locations;
	
	std::unordered_map<std::string, Item*> constructItems(ADVENTURES current_adventure);
	std::vector<Location*> constructLocations(ADVENTURES current_adventure);
	void cacheSaveData(int choice);
	void loadLocationBase();
	void loadLocationItems();
	void loadLocationExits();
	
public:
	AdventureSelectMenu();
	~AdventureSelectMenu();

	void setWorldLoader(WorldLoader* world_loader);
	std::vector<Location*> returnLocationData();
	STATES update() override;
	void render() override;
};

class GameplayState : public State {
private:
	std::vector<Location*> _location_data;
	Location* _current_location;

public:
	GameplayState(std::vector<Location*> location_data = {});

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