#include <vector>

#include "GameData.h"
#include "../../Components/hdr/C_Render.h"
#include "../../Components/hdr/C_Spatial.h"
#include "../../Components/hdr/C_Inventory.h"

#pragma once

/*	Think of a little garage attached to the factory whose purpose is to give me
*	the components needed for the entities such that they can be assembled
*
*	it takes a lowercase string in the form:
*		"ComponentFlag0(arg0,arg1), ComponentFlag1(arg0,arg1), ..."			  */
class ComponentFactory {
private:
	GameData* _game_data = nullptr;
	std::vector<std::string> _raw_component_dataset;
	std::vector<std::vector<std::string>> _fmt_component_dataset;

	std::vector<std::string> splitSaveLine(std::string& line, const char delimiter);
	std::vector<std::vector<std::string>> formatComponentData();
	ComponentFlag determineFlag(const std::string flag);
	std::vector<std::string> formatArgs(std::vector<std::string>& component_data);
	void createComponent(int entity_id, std::vector<std::string>& component_data);

public:
	ComponentFactory(GameData* game_data);

	void setComponentData(std::vector<std::string> component_data);
	void constructComponents(int entity_id);
};