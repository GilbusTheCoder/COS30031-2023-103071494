#include "Component.h"

#pragma once
/*	Allows for movement and looking to occur, used on the player
*	only right now												*/
class C_Spatial : public Component {
private:
	int _entity_id = 999999999;
	ComponentFlag _flag = ComponentFlag::SPATIAL;

	bool _has_eyes = true;
	bool _has_arms = true;
	bool _has_legs = true;

public:
	C_Spatial(int owning_entity_id);
	ComponentFlag getFlag() override;

	bool hasEyes();
	bool hasArms();
	bool hasLegs();

	void setEyes(bool has_eyes);
	void setArms(bool has_arms);
	void setLegs(bool has_legs);

	void update() override;
	void render() override;
};