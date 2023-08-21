/*	Gridworld (but cooler) -- Thomas Horsley / 103071494
*	
*	This is a multithreaded version of Task 03 - Spike 'Gridworld'
*	Essentially the update and render functions have a dedicated
*	worker thread and the player input is handled by seperate thread.
* 
*	This allows for the decoupling of these two functions meaning the
*	world may update and render itself to console without waiting for
*	player input, allowing for a more dynamic and realistic world. */

#include<thread>
#include "World.h"

int main() {
	World world;
	while (world.getGameRunning() == true) {
		world.update();
		world.render();
	}

	return 0;
}

