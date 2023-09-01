#include "World.h"

/*	Task: Task 11 - Spike
*	Title: Game Data From Graphs
*	Author: Thomas Horsley - 103071494
* 
*	Currently:	Add a player object which will have a reference to the current location.
*				A player does not exist within the location it exists within the world
*				
* 
*	Completed:  Working on using a file reader to instantiate the location game object
*			    and there-in the world object from a text file, could use JSON later.	
* 
*				Will probably end up making the world object more of a world "manager" 
*				class. So given this, we're giving it the ability to read and write saves
*				and it will have access to the player object.
* 
*				Chopped up the big main.cpp into a bunch of more managable header and 
*				implementation files. Also fixed my inconsistent af naming.
* 
* 
*		Formatting:
*			To make life easier with the functions that I've already written we're going
*			to split the txt file using a double delimiter tech.
*				* Delimit once to split the file by location
*					This will return a vector of strings
*				* Iterate through each vector and split their strings into another set 
*				  of vectors.
*				* Use this data to instantiate location objects 
* 
*	Summary:
*		So I don't really like this code to be honest. It works yes but instantiation of
*		locations is a really fickle fucker. Additionally the order of the location data
*		must be the same as the order of the locations in the vector. This is an issue for
*		now as the program doesn't write its own save files. Cuz i wrote it and it's stoop.
* 
*		World has a set of location pointers. It can read from a file and assign the input
*		data to the locations. 
* 
* 
*		Next step is to implement world traversal before chopping this up into class files 
*		for organisation and shove it into zorkish.......... this is going to be fun and easy :)
*/ 

int main() {
	//Ahhhhhhh what a nice clean main :)
	World world;

	world.loadLocationData();
	world.showLocations();
}