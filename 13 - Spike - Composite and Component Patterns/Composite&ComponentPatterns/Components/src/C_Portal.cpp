#include "../hdr/C_Portal.h"

C_Portal::C_Portal(std::string entity_id, Entity* exit) {
}

void C_Portal::setExit(Entity* exit) { 
	if(exit != nullptr) _exit = exit; }


Entity* C_Portal::getExit() { return _exit; }
