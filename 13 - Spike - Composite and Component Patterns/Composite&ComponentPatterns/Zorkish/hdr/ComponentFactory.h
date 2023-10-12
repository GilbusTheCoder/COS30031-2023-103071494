#include <vector>

#include "GameData.h"
#include "../../Components/hdr/C_Render.h"
#include "../../Components/hdr/C_Spatial.h"
#include "../../Components/hdr/C_Inventory.h"
#include "../../Components/hdr/C_Portal.h"

#pragma once

/*	Think of a little garage attached to the factory whose purpose is to give me
*	the components needed for the entities such that they can be assembled
*
*	it takes a lowercase string in the form:
*		"ComponentFlag0(arg0,arg1)|ComponentFlag1(arg0,arg1)|..."			  */
class ComponentFactory {
private:
	GameData* _game_data = nullptr;
	std::vector<std::string> _raw_component_dataset;
	std::vector<std::vector<std::string>> _fmt_component_dataset;

	void formatComponentData();
	std::vector<std::string> formatArgs(std::vector<std::string>& c_data);
	std::vector<std::string> splitSaveLine(std::string& line, const char delimiter);

	void instanceCSpatial(std::string ec_id);
	void instanceCRender(std::string ec_id, 
		std::string& name, std::string& description);
	void instanceCInventory(std::string ec_id, std::vector<std::string> items);
	void instanceCPortal(std::string ec_id, std::vector<std::string> args);

	ComponentFlag determineFlag(const std::string flag);
	void createComponent(std::string entity_id, ComponentFlag c_flag,
		int c_id, std::vector<std::string>& c_args);

public:
	ComponentFactory(GameData* game_data);
	~ComponentFactory();

	std::string extractUEID(std::string cuid);
	void setComponentData(std::vector<std::string>& component_data);
	void constructComponents(std::string entity_id, bool new_entity = true);
};