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

};