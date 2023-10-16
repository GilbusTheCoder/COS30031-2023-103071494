#include "../hdr/C_Portal.h"

/******************************************************************************
*							    De/Constructors
******************************************************************************/
C_Portal::C_Portal(std::string ucid, std::string direction,
	Entity* exit) : _ucid(ucid), _dir(direction), _exit(exit) { 

}


/******************************************************************************
*								  Properties
******************************************************************************/
ComponentFlag C_Portal::getFlag() {return _flag; }
std::string C_Portal::getDirection() { return _dir; }
Entity* C_Portal::getExit() { return _exit; }

void C_Portal::setExit(Entity* exit) { if(exit != nullptr) _exit = exit; }

/******************************************************************************
*								     Loop
******************************************************************************/
void C_Portal::update() { }

void C_Portal::render() { }