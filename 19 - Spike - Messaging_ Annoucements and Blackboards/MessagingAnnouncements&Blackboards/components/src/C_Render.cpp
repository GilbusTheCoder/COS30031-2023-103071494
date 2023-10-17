#include <iostream>
#include <algorithm>
#include "../hdr/C_Render.h"

/******************************************************************************
*							    De/Constructors
******************************************************************************/
C_Render::C_Render(std::string ucid, std::string name,
	std::string description, bool render_this)
	:_ucid(ucid), _render_this(render_this) {
	setName(name);
	setDescription(description);
}

/******************************************************************************
*								  Properties
******************************************************************************/
ComponentFlag C_Render::getFlag() { return _flag; }
std::string C_Render::getName() { return _name; }
std::string C_Render::getDescription() { return _description; }
bool C_Render::renderThis() { return _render_this; }


void C_Render::flagForRender(bool yes_or_no) { _render_this = yes_or_no; }
void C_Render::setName(std::string name) {
	std::replace(name.begin(), name.end(), '_', ' ');
	if (name.back() == ',') { name.resize(name.size() - 1); }
	_name = name;
}
void C_Render::setDescription(std::string description) {
	std::replace(description.begin(), description.end(), '_', ' ');
	if (description.back() == ',') {
		description.resize(description.size() - 1);
	}
	_description = description;
}


/******************************************************************************
*								  Methods
******************************************************************************/
void C_Render::update() {}
void C_Render::render() {
	std::cout << "Name -> " << _name << "\n";
	std::cout << "Description -> " << _description << "\n";
}
