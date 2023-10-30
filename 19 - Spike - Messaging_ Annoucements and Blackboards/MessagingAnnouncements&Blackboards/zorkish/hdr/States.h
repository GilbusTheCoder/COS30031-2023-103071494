#include "WorldLoader.h"
#include "EventDispatcher.h"
#include "InputHandler.h"

#pragma once
enum STATES {
	S_WELCOME,
	S_MAIN_MENU,
	S_ABOUT,
	S_HELP,
	S_SELECT_ADVENTURE,
	S_GAMEPLAY,
	S_NEW_HS,		//New Highscore
	S_VIEW_HoF,	//View Hall of Fame
	S_QUIT,
};

class State {
public:
	GameData* _game_data = nullptr;

	virtual void setStateData(GameData* game_data = nullptr,
		std::vector<std::string> args = {}) = 0;

	virtual STATES update() = 0;
	virtual void render() = 0;
};


class MainMenu : public State {
public:
	void setStateData(GameData* game_data = nullptr,
		std::vector<std::string> args = {}) override;


	STATES update() override;
	void render() override;
};

class AboutMenu : public State {
public:
	void setStateData(GameData* game_data = nullptr,
		std::vector<std::string> args = {}) override;

	STATES update() override;
	void render() override;
};

class HelpMenu : public State {
public:
	void setStateData(GameData* game_data = nullptr,
		std::vector<std::string> args = {}) override;

	STATES update() override;
	void render() override;
};

class AdventureSelectMenu : public State {
private:
	WorldLoader* _world_loader = nullptr;

public:
	AdventureSelectMenu();
	~AdventureSelectMenu();

	void setStateData(GameData* game_data = nullptr,
		std::vector<std::string> args = {}) override;

	STATES update() override;
	void render() override;
};

class GameplayState : public State {
private:
	bool first_pass = true;

	InputData* _input_data = new InputData();
	InputHandler* _input_handler = nullptr;
	EventDispatcher* _event_dispatcher = nullptr;

public:
	GameplayState();
	~GameplayState();

	void setStateData(GameData* game_data = nullptr,
		std::vector<std::string> args = {}) override;

	STATES update() override;
	void render() override;

private:
	std::string extractUEID(std::string ucid);
	void resetRender();
};

class NewHighScoreMenu : public State {
public:
	void setStateData(GameData* game_data = nullptr,
		std::vector<std::string> args = {}) override;

	STATES update() override;
	void render() override;
};

class HallOfFameMenu : public State {
public:
	void setStateData(GameData* game_data = nullptr,
		std::vector<std::string> args = {}) override;

	STATES update() override;
	void render() override;
};

class QuitState : public State {
public:
	void setStateData(GameData* game_data = nullptr,
		std::vector<std::string> args = {}) override;

	STATES update() override;
	void render() override;
};