#pragma once
class World {
private:
	int mapSize = 64;
	int playerPosition = 49; //Value corresponding element S
	bool gameRunning = true;
	
	void introSec();
	char* constructWorld();

	//Only presents movement directions, ommits default array values
	char* findValidMoves();
	void presentValidMoves();
	char getInput();
	void handleInput();
	void handleEvents();

	void printMap();

public:
	World();
	bool getGameRunning();
	void update();
	void render();
};

