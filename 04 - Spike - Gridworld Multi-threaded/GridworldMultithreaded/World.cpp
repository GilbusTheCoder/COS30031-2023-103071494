/*	The master class, holds all of the game logic relating to 
*	handling player input, updating the gamestate and rendering
*	that state to the console. */

/* TODO: Gotta make the map a dynamic array which can be modified
*		 to output real time visuals. */

#include <iostream>
#include "World.h"

World::World() {
	char* map = constructWorld();

	introSec();
	render();
}

void World::introSec() {
	std::cout << "Welcome to Gridworld: Quantised Excitement!" << std::endl;
	std::cout << "------------------------------------------------------------------------" << std::endl;
	std::cout << std::endl;

	std::cout << "Fate is waiting for you! (Coder: Thomas Horsley - 103071494)" << std::endl;
	std::cout << "Valid commands: N, E, S & W for Direction. Q to quit" << std::endl;
	std::cout << std::endl;
}

char* World::constructWorld() {
	char* world = new char[64];

	for (int i = 0; i < 64; i++) {
		if (i < 8 || i > 55) { world[i] = '#'; } //Top and bottom borders
		else if (i%8 == 1 || i%8 == 7) { world[i] = '#'; } //left right borders
	}

	return world;
}

char* World::findValidMoves() {
	//* Dynamic arrays are pretty cewl, I'm assuming it's auto-deleted when
	//* out of scope.
	char* validMoves = new char[4];

	//'T' is a default value loaded for later presentation functions
	for (int i = 0; i < 4; i++) { validMoves[i] = 'T'; }
	
	if (map[playerPosition - 8] != '#') { validMoves[0] = 'N'; }
	if (map[playerPosition + 1] != '#') { validMoves[1] = 'E'; }
	if (map[playerPosition + 8] != '#') { validMoves[2] = 'S'; }
	if (map[playerPosition - 1] != '#') { validMoves[3] = 'W'; }
	
	return validMoves;
}

void World::handleEvents() {
	if (map[playerPosition] == '^') {
		std::cout << "AH! Man's hit a spike!" << std::endl;
		gameRunning = false;
	}
	if (map[playerPosition] == 'G') {
		std::cout << "Good job, you got the goop!" << std::endl;
		gameRunning = false;
	}
}
void World::presentValidMoves() {
	char* validMoves = findValidMoves();

	std::cout << "You can move: ";

	for (int i = 0; i < 4; i++) {
		if (validMoves[i] != 'T') { std::cout << validMoves[i] << ", "; }
	}
	std::cout << std::endl;
}

void World::handleInput() {
	switch (getInput()) {
	case 'N':
		playerPosition -= 8;
		break;
	case 'E':
		playerPosition += 1;
		break;
	case 'S':
		playerPosition += 8;
		break;
	case 'W':
		playerPosition -= 1;
		break;
	case 'Q':
		gameRunning = false;
		break;
	default:
		playerPosition += 0;
		break;
	}
}

void World::printMap() {
	for (int count = 0; count < 64; count++) {
		if (count % 8 == 7) { std::cout << map[count] << std::endl; }
		else { std::cout << map[count]; }
	}
}

bool World::getGameRunning() { return gameRunning; }

char World::getInput() {
	char input;
	std::cin >> input;
	char upper_case_char = toupper(input);

	return upper_case_char;
}

void World::update() {
	handleInput();
	handleEvents();
}

void World::render() {
	printMap();
	presentValidMoves();
}