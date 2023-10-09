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

/*	Load and instantiate our entity objects based off a file. */
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