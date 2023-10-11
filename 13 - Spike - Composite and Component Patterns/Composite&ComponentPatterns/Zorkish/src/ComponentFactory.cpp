#include <iostream>
#include <algorithm>
#include "../hdr/ComponentFactory.h"

/******************************************************************************
*							    De/Constructors
******************************************************************************/
ComponentFactory::ComponentFactory(GameData* game_data)  {
	if (game_data != nullptr ) { _game_data = game_data; } 
	else { std::cout << "Err: Bad F_Component instantiation.\n"; }
}

ComponentFactory::~ComponentFactory() { }

/******************************************************************************
*							     Private Methods
******************************************************************************/


/*	Creates a vector<vector<string>> in the form:
*	   <<ComponentFlag, "Args, Args">,
*		<...>,
*		<ComponentFlag, "Args, ..., Args">>									 */
void ComponentFactory::formatComponentData() {
	/*  Break up the string into a vector with the Comp flag first and args
	*	in their own proceeding elements									 */
	if (!_raw_component_dataset.empty()) {
		for (std::string& component : _raw_component_dataset) {
			std::vector<std::string> formatted_data;

			size_t flag_start_idx = 0,
				flag_end_idx = component.find_first_of('('),
				args_start_idx = flag_end_idx + 1,
				args_end_idx = component.size() - 2;

			formatted_data.emplace_back(
				component.substr(flag_start_idx, flag_end_idx));
			formatted_data.emplace_back(
				component.substr(args_start_idx, args_end_idx));

			formatted_data.back().resize(formatted_data.back().size() - 1);

			_fmt_component_dataset.emplace_back(formatted_data);
		}
	}
}

/*	The vector at this point should only be 1 element containing a list of
*	arguments seperated via comma. <"arg1, arg2, ..., argN">
*	Take these arguments and seperate them into their own elements. The context
*	of the arguments is assumed by the flag but that is handled in the
*	createComponent methods anyways											*/
std::vector<std::string> ComponentFactory::formatArgs
(std::vector<std::string>& c_data) {
	std::vector<std::string> fmt_args;

	for (auto& component_datum : c_data) {
		fmt_args = splitSaveLine(component_datum, ',');	}

	return fmt_args;
}

std::vector<std::string> ComponentFactory::splitSaveLine(std::string& line,
	const char delimiter) {
	int start_idx = 0, end_idx = 0;
	std::string raw_line_data = line += delimiter;
	std::vector<std::string> formatted_line_data;

	for (int idx = 0; idx <= raw_line_data.size(); idx++) {
		if (char(raw_line_data[idx]) == delimiter) {
			std::string line_datum;
			end_idx = idx;

			line_datum.append(raw_line_data, start_idx, end_idx - start_idx);
			formatted_line_data.emplace_back(line_datum);

			start_idx = ++end_idx;
		}
	}

	return formatted_line_data;
}

std::string ComponentFactory::extractEUID(std::string cuid) {
	// Check each character of the cuid until we hit an upper case letter
	// take all the characters from before the upper case and that's our EUID
	// to return.
	std::string::iterator cuid_it;
	std::string EUID;
	
	for (cuid_it = cuid.begin(); cuid_it != cuid.end(); cuid_it++) {
		if (char(*cuid_it) > 96 && char(*cuid_it) < 123) {
			std::string EUID_element(1, char(*cuid_it));
			EUID.append(EUID_element);
		}
		else { return EUID; }
	}
	
	return EUID;
}



void ComponentFactory::instanceCSpatial(std::string ec_id) {
	C_Spatial* new_spatial = new C_Spatial(ec_id);
	_game_data->c_spatials.insert({ ec_id, new_spatial });
}

void ComponentFactory::instanceCRender(std::string ec_id, std::string name, 
	std::string description) {
	C_Render* new_renderer = new C_Render(ec_id, name, description);
	_game_data->c_renderers.insert({ ec_id, new_renderer });
}

// Inventory can't find items again
void ComponentFactory::instanceCInventory(std::string ec_id,
	std::vector<std::string> items) {
	C_Inventory* new_inventory = nullptr;
	std::vector<InventorySlot*> slots;

	if (items.empty()) { new_inventory = new C_Inventory(ec_id); }
	else {
		for (std::string item_name : items) {
			if (item_name.find_first_of('_') != std::string::npos) {
				std::replace(item_name.begin(), item_name.end(), '_', ' '); }

			if (item_name.back() == ',') {
				item_name.resize(item_name.size() - 1); }

			std::map<std::string, C_Render*>::iterator traversal_it;
			for (traversal_it = _game_data->c_renderers.begin();
				traversal_it != _game_data->c_renderers.end(); traversal_it++) {
				if (traversal_it->second->getName() == item_name) {
					std::string lookup_id = extractEUID(traversal_it->first);
					InventorySlot* new_slot = new InventorySlot(_game_data->entities.find(lookup_id)->second);
					slots.emplace_back(new_slot);
					break;
				}
			}
		} new_inventory = new C_Inventory(ec_id, slots);
	} _game_data->c_inventories.insert({ ec_id, new_inventory });
}



ComponentFlag ComponentFactory::determineFlag(const std::string flag) {
	if (flag == "render") { return ComponentFlag::RENDER; }
	if (flag == "spatial") { return ComponentFlag::SPATIAL; }
	if (flag == "inventory") { return ComponentFlag::INVENTORY; }
	return ComponentFlag::INVALID;
}

void ComponentFactory::createComponent(std::string entity_id, ComponentFlag c_flag,
	int c_id, std::vector<std::string>& c_args) {
	std::string C_ID(1, c_id);
	std::string EC_ID = entity_id.append(C_ID);

	// If args aren't required then put it at the top
	if (c_flag == ComponentFlag::SPATIAL) { instanceCSpatial(EC_ID); } 
	
	std::vector<std::string> component_args = formatArgs(c_args);
	if (c_flag == ComponentFlag::RENDER) { 
		instanceCRender(EC_ID, c_args[0], c_args[1]); }

	if (c_flag == ComponentFlag::INVENTORY) {
		instanceCInventory(EC_ID, c_args); 	}
}

/******************************************************************************
*							     Public Methods
******************************************************************************/
void ComponentFactory::setComponentData(std::vector<std::string> component_data) {
	if (component_data.empty()) { _raw_component_dataset = component_data; }
	else {
		_raw_component_dataset.clear();
		_raw_component_dataset.shrink_to_fit();
		_raw_component_dataset = component_data;
	};
}

void ComponentFactory::constructComponents(std::string entity_id) {
	std::vector<Component*> components;

	int component_id = 65;		// Using capital letters for the ascii
	if (!_raw_component_dataset.empty()) {
		formatComponentData();

		// Only allow for 26 components. More should be unnecessary
		for (std::vector<std::string> component_data : _fmt_component_dataset) {
			if (component_id < 91) {
				std::string str_flag = *component_data.begin();
				component_data.erase(component_data.begin());
				component_data.shrink_to_fit();

				std::vector<std::string> component_args = splitSaveLine(component_data[0], ',');
				
				ComponentFlag flag = determineFlag(str_flag);
				createComponent(entity_id, flag, component_id, component_args);
		
				component_id++;
			}
		}

		_fmt_component_dataset.clear();
		_fmt_component_dataset.shrink_to_fit();
	}
}

