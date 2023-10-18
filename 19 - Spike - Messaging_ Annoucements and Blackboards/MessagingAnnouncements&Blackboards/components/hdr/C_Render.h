#include "Component.h"

#pragma once

// Required for items to display a name and description to screen
class C_Render : public Component {
private:
	std::string _ucid;
	ComponentFlag _flag = ComponentFlag::C_RENDER;

	std::string _name;
	std::string _description;
	bool _render_this = false;

public:
	C_Render(std::string ucid, std::string name,
		std::string description, bool render_this = false);

	ComponentFlag getFlag() override;
	std::string getName();
	std::string getDescription();
	bool renderThis();

	void setName(std::string name);
	void setDescription(std::string description);
	void flagForRender(bool yes_or_no);

	void onEvent() override;
	std::vector<std::string> getInfo() override;
};