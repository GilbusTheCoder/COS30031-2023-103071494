#include "../hdr/C_Spatial.h"

C_Spatial::C_Spatial(std::string owning_entity_id, bool has_eyes, bool has_arms, bool has_legs) 
	: _entity_id(owning_entity_id), _has_eyes(has_eyes), 
	  _has_arms(has_arms), _has_legs(has_legs)  { }

ComponentFlag C_Spatial::getFlag() { return _flag; }

bool C_Spatial::hasEyes() { return _has_eyes; }
bool C_Spatial::hasArms() { return _has_arms; }
bool C_Spatial::hasLegs() {	return _has_legs; }

void C_Spatial::setEyes(bool has_eyes) { _has_eyes = has_eyes; }
void C_Spatial::setArms(bool has_arms) { _has_arms = has_arms; }
void C_Spatial::setLegs(bool has_legs) { _has_legs = has_legs; }

void C_Spatial::update() { }
void C_Spatial::render() { }
