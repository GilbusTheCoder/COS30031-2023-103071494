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
std::vector<std::string> ComponentFactory::splitSaveLine(std::string& line, 
	const char delimiter){
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

ComponentFlag ComponentFactory::determineFlag(const std::string flag)
{
	if (flag == "render") { return ComponentFlag::RENDER; }
	if (flag == "spatial") { return ComponentFlag::SPATIAL; }
	if (flag == "inventory") { return ComponentFlag::INVENTORY; }
	return ComponentFlag::INVALID;
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
		fmt_args = splitSaveLine(component_datum, ',');
	}

	return fmt_args;
}

/*	Im going to preface this method with the old "I don't care about performance
*	this is a load screen and it's 1am excuse. Enjoy the nested loops		  */ 
void ComponentFactory::createComponent(int entity_id, ComponentFlag c_flag,
	std::vector<std::string>& c_args) {
	/* Spatial case should be modified to take has_x args from the list.     */
	if (c_flag == ComponentFlag::SPATIAL) {
		C_Spatial* new_spatial = new C_Spatial(entity_id);
		_game_data->c_spatials.insert({ entity_id, new_spatial });
		return;
	}
	
	std::vector<std::string> component_args = formatArgs(c_args);
	if (c_flag == ComponentFlag::RENDER) {
		C_Render* new_renderer = new C_Render(entity_id, 
			component_args[0], component_args[1]);
		
		_game_data->c_renderers.insert({ entity_id, new_renderer });
		return;
	}

	/*	Don't worry about loading items when loading the inventory as it's 
	*	assumed they're the first dataset in the save file and therefore already
	*	exist as entities with rendered names which can be referenced		*/
	if (c_flag == ComponentFlag::INVENTORY) {
 		C_Inventory* new_inventory = nullptr;
		if (component_args.empty()) { 
			new_inventory = new C_Inventory(entity_id); 
			_game_data->c_inventories.insert({ entity_id, new_inventory });
		} else {
			/*	If this case is triggered then there were items in the inventory.
			*	These items already exist in the GameData and have renders, meaning
			*	they have names we can search.									*/
			C_Render* current_renderer = nullptr;
			std::vector<InventorySlot*> slots;

			for (std::string item_name : component_args) {
				if (item_name.find_first_of('_') != std::string::npos) {
					std::replace(item_name.begin(), item_name.end(), '_', ' ');
				}

				if (item_name.back() == ',') {
					item_name.resize(item_name.size() - 1);	}

				for (auto idx = _game_data->c_renderers.begin();
					idx != _game_data->c_renderers.end(); ++idx) {
					if (idx->second->getName() == item_name) {
						// Get the id of the entity it's attached to for ref
						int entity_id = idx->first;

						Entity* item = _game_data->entities.find(entity_id)->second;
						InventorySlot* new_slot = new InventorySlot(item);

						slots.emplace_back(new_slot);
						break;
					}
				}
			}

			new_inventory = new C_Inventory(entity_id, slots);
			_game_data->c_inventories.insert({ entity_id, new_inventory });
			return;
		}
	}
}


void ComponentFactory::setComponentData(std::vector<std::string> component_data) {
	if (component_data.empty()) { _raw_component_dataset = component_data; }
	else {
		_raw_component_dataset.clear();
		_raw_component_dataset.shrink_to_fit();
		_raw_component_dataset = component_data;
	};
}

/******************************************************************************
*							     Public Methods
******************************************************************************/
void ComponentFactory::constructComponents(int entity_id) {
	std::vector<Component*> components;
	
	if (!_raw_component_dataset.empty()) {
		formatComponentData();

		for (std::vector<std::string> component_data : _fmt_component_dataset) {
			std::string str_flag = *component_data.begin();
			component_data.erase(component_data.begin());
			component_data.shrink_to_fit();
		
			ComponentFlag flag = determineFlag(str_flag);
			createComponent(entity_id, flag, component_data);
		}

		_fmt_component_dataset.clear();
		_fmt_component_dataset.shrink_to_fit();
	}
}

