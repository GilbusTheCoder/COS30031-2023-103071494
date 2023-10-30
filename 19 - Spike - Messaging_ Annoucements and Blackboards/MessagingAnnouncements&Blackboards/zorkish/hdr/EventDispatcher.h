#include <vector>
#include <queue>

#include "InputData.h"
#include "../../commands/hdr/LookCommand.h"
#include "../../commands/hdr/MoveCommand.h"
#include "../../commands/hdr/QuitCommand.h"
#include "../../commands/hdr/ShowCommand.h"
#include "../../commands/hdr/TakeCommand.h"

#pragma once

/*	This is the thing responsible for dispatching trigger messages to the
*	relevant entities and components.
* 
*	This needs:
*		--> Ability to add entities and components to an address list
*				-->	This system will be built such that only relevant Entities
*					and components are registered (such as the location and it's
*					contents).
*		--> Ability to unsubscribe entities for on event changes
*		--> Ability to take a message from an InputHandler and trigger the relevant
*			Command with the relevant arguments.
*				--> Needs to filter to the correct Entities / Components
*				--> Needs to be able to pass these Entities and Components to the 
*					relevant Commands onEvent(args)
*				--> notify
* 
*	InputHandler needs:
*		--> Takes a stringstream input from the user and 
* 
*	GameData needs:
*		--> To hold a list of our Command* as well as our Entities and Components
*			
* 
*	The Entities and Components need:
*		--> Rebuild the inventory so that it works pls
* 
*	The Commands need to be able to:
*		--> Take generic arguments (such as inventory1 and inventory2 for take/drop)
*				--> This will allow them to be notified by the eventDispatcher to do
*					a thing given generic args.
* 
*	---- Commonalities between modifications ----
*	1.
*/

class EventDispatcher {
private:
	GameData* _game_data = nullptr;

	MoveCommand* _move_command = nullptr;
	TakeCommand* _take_command = nullptr;
	LookCommand* _look_command = nullptr;
	ShowCommand* _show_command = nullptr;
	QuitCommand* _quit_command = nullptr;

public:
	// Create all the commands within the _commands vector
	EventDispatcher();
	~EventDispatcher(); // Delete commands

	void setGameData(GameData* game_data);
	void filterLocalComponents();
	void resetComponents();

	// Call the onEvent() method for the relevant commands parsing the relevant args
	std::queue<Command*> processEvents(InputData* input_data);

private:
	void getEntityComponents(const char UEID);
	C_Render* getRenderer(const char UEID);
	C_Inventory* getInventory(const char UEID);
	std::vector<C_Portal*> getPortals(const char UEID);

	std::string getExitUEIDFromDir(std::string direction);
};