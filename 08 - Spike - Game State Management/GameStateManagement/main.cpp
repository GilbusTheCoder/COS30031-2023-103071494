/*	Task 08 - Game State Management
*	Author - Thomas Horsley (103071494)
* 
*	The state manager was built implementing the OO State pattern.
	See spike report! */

#include <iostream>
#include <string>

enum STATES {
	MAIN_MENU,
	ABOUT,
	HELP,
	SELECT_ADVENTURE,
	GAMEPLAY,
	NEW_HS,		//New Highscore
	VIEW_HoF,	//View Hall of Fame
	QUIT,
	FINISHED,	//Final state of the game.
};

class State {
public:
	//Each update function will return a pointer to the state
	virtual STATES update() = 0;
	virtual void render() = 0;
};

class MainMenu : public State {
public:
	STATES update() override { return STATES::GAMEPLAY; }

	void render() override {
		std::cout << "Main menu stuff and what-not" << std::endl;
	}
};

class Gameplay : public State {
public:
	STATES update() override { return STATES::QUIT; }

	void render() override { 
		std::cout << "Gameplay stuff goes in here!" << std::endl; 
		}
};

class Quit : public State {
public:
	//WOWO Make sure old mate wants to quit first!
	STATES update() override { return STATES::FINISHED; }

	void render() override {
		std::cout << "Quitting zorkish!" << std::endl;
	}
};

class GameStateManager {
private:
	MainMenu _main_menu;
	Gameplay _gameplay;
	Quit _quit;

	State* _current_ptr = nullptr;
	STATES _current_state = STATES::MAIN_MENU;

public:
	bool isRunning() { return _current_state != STATES::FINISHED; }

	void update() {
		if(_current_state == STATES::MAIN_MENU) { _current_ptr = &_main_menu; }
		else if (_current_state == STATES::GAMEPLAY) { _current_ptr = &_gameplay; }
		else if (_current_state == STATES::QUIT) { _current_ptr = &_quit; }

		//Wrapped up all nice and cozy
		_current_state = _current_ptr->update();
	}

	void render() {
		_current_ptr->render();
	}
};

int main() {
	GameStateManager _game_manager;

	while (_game_manager.isRunning()) {
		_game_manager.update();
		_game_manager.render();
	}

	return 0;
}