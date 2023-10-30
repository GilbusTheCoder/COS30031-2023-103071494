#include <map>

#include "../hdr/Entity.h"
#include "../../Components/hdr/C_Render.h"
#include "../../Components/hdr/C_Inventory.h"
#include "../../Components/hdr/C_Portal.h"


/*	This is the dataset which gets instantiated in the AdventureSelectMenu
*	before being passed to the GameplayState for play-time manipulation		 */

//	Try character maps floats are fucking shit
#pragma once
struct GameData {
	bool is_running = true;
	bool reinstance_local_entity_cache = true;
	bool discovered_area = false;

	std::string player;
	std::string current_location;
	std::map<std::string, Entity*> entities;
	
	std::map<std::string, C_Render*> c_renderers;
	std::vector<C_Render*> _local_renderers;

	std::map<std::string, C_Inventory*> c_inventories;
	std::vector<C_Inventory*> _local_inventories;
	
	std::map<std::string, C_Portal*> c_portals;
	std::vector<C_Portal*> _local_portals;
};

