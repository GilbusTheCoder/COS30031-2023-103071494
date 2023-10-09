#include <iostream>
#include "Component.h"

#pragma once

// Required for items to display a name and description to screen
class C_Render : public Component {
private:
	int _entity_id = 999999999;
	ComponentFlag _flag = ComponentFlag::RENDER;

	std::string _name;
	std::string _description;
	bool _render_this = true;

public:
	C_Render(int owning_entity_id, std::string name, std::string description);

	ComponentFlag getFlag() override;
	std::string getName();
	std::string getDescription();
	void flagForRender(bool yes_or_no);
	void setName(std::string name);
	void setDescription(std::string description);

	void update() override;
	void render() override;
};