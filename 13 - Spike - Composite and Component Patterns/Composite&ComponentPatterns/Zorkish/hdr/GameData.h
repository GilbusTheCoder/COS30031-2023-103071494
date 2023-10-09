#include <unordered_map>

#include "../hdr/Entity.h"
#include "../../Components/hdr/C_Render.h"
#include "../../Components/hdr/C_Spatial.h"
#include "../../Components/hdr/C_Inventory.h"

#pragma once
struct GameData	{
	bool is_running = true;

	std::unordered_map<int, Entity*> entities;
	std::unordered_map<int, C_Render*> c_renderers;
	std::unordered_map<int, C_Inventory*> c_inventories;
	std::unordered_map<int, C_Spatial*> c_spatials;

	Entity* player;
	Entity* current_location;
}; 

