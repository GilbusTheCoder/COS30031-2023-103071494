#include "Component.h"

#pragma once
/*	Allows for movement and looking to occur, used on the player
*	only right now												*/
class C_Spatial : public Component {
private:
	std::string _ucid;
	ComponentFlag _flag = ComponentFlag::C_SPATIAL;

	bool _has_eyes = true;
	bool _has_arms = true;
	bool _has_legs = true;

public:
	C_Spatial(std::string ucid, bool has_eyes=true, bool has_arms=true, 
		bool has_legs=true);
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