#include "../hdr/C_Portal.h"

/******************************************************************************
*							    De/Constructors
******************************************************************************/
C_Portal::C_Portal(std::string owning_entity_id, std::string direction,
	Entity* exit) : _entity_id(owning_entity_id), _dir(direction), _exit(exit) { 

}


/******************************************************************************
*								  Properties
******************************************************************************/
ComponentFlag C_Portal::getFlag() {return _flag; }
Entity* C_Portal::getExit() { return _exit; }
std::string C_Portal::getDirection() { return _dir; }

void C_Portal::setExit(Entity* exit) { if(exit != nullptr) _exit = exit; }


/******************************************************************************
*								     Loop
******************************************************************************/
void C_Portal::update() { }

void C_Portal::render() { }