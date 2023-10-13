#include <map>

#include "../hdr/Entity.h"
#include "../../Components/hdr/C_Render.h"
#include "../../Components/hdr/C_Spatial.h"
#include "../../Components/hdr/C_Inventory.h"
#include "../../Components/hdr/C_Portal.h"


/*	This is the dataset which gets instantiated in the AdventureSelectMenu
*	before being passed to the GameplayState for play-time manipulation		 */

//	Try character maps floats are fucking shit
#pragma once
struct GameData	{
	bool is_running = true;

	std::map<std::string, Entity*> entities;
	std::map<std::string, C_Render*> c_renderers;
	std::map<std::string, C_Inventory*> c_inventories;
	std::map<std::string, C_Spatial*> c_spatials;
	std::map<std::string, C_Portal*> c_portals;

	std::string player;
	std::string current_location;
}; 

