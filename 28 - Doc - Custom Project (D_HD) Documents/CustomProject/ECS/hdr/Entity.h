#include <string>

#pragma once
/*	Entities act as links between components and systems. They do not hold any other purpose
*	The ID of the entity is prefixed to the ID of each component. This allows relevant 
*	systems to search for components belonging to the same Entity. 
* 
*	The entities ID will be a set of capital characters 'A' or 'AB'.					
	The components ID will look like 'Aa' or 'Aab' or 'ACadx' something like that		*/

namespace ECS {
	typedef std::string entity_id;
	struct Entity { entity_id id; }; }

