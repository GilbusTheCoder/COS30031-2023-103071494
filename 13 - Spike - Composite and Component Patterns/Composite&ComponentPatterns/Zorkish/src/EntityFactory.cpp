#include <algorithm>
#include "../hdr/EntityFactory.h"

/******************************************************************************
*							    De/Constructors
******************************************************************************/
//	Must pass the game data on instantiation or this class is less than useless
EntityFactory::EntityFactory(GameData* game_data,
	std::vector<std::vector<std::string>> entity_data) : _game_data(game_data) {
	if (!entity_data.empty()) { _raw_entity_dataset = entity_data; }

	if (_component_factory == nullptr) { 
		_component_factory = new ComponentFactory(_game_data); 
	} else {
		delete _component_factory;
		_component_factory = nullptr;
		_component_factory = new ComponentFactory(_game_data); 
	}

	if (_game_data == nullptr || _component_factory == nullptr) {
		std::cout << "Err: Bad F_Entity instantiation.\n";
	}
}

EntityFactory::~EntityFactory() {
	if (_component_factory != nullptr) {
		delete _component_factory;
		_component_factory = nullptr;
	}
}

/******************************************************************************
*							    Private Methods
******************************************************************************/
EntityTag EntityFactory::determineTag(std::string tag) {
	if (tag.find_first_of('_') != tag.size()) {
		std::replace(tag.begin(), tag.end(), '_', ' ');	}

	if (tag == "player") { return EntityTag::PLAYER; }
	if (tag == "location") { return EntityTag::LOCATION; }
	if (tag == "item") { return EntityTag::ITEM; }
	if (tag == "current location") { return EntityTag::CURRENT_LOCATION; }
	return EntityTag::INVALID;
}

Entity* EntityFactory::createEntity(std::vector<std::string> entity_data) {
	EntityTag entity_tag = determineTag(entity_data[0]);
	entity_data.erase(entity_data.begin());
	entity_data.shrink_to_fit();			// Only element left contains components

	/*	Pass the component_factory component args in the form:
	*		<ComponentFlag0(arg0,arg1)|ComponentFlag1(arg0,arg1), ...>			  */
	std::vector<std::string> component_data;
	if (entity_data[0].find("|") != std::string::npos) {
		component_data = splitSaveLine(entity_data[0], '|');
	} else { component_data = entity_data;}

	_component_factory->setComponentData(component_data);
	_component_factory->constructComponents(entity_id);


	Entity* entity = new Entity(entity_id, entity_tag);
	entity_id++;
	return entity;
}

std::vector<std::string> EntityFactory::splitSaveLine(std::string& line, 
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


/******************************************************************************
*							     Public Methods
******************************************************************************/
void EntityFactory::setEntityData(std::vector<std::vector<std::string>> entity_data)
	{ _raw_entity_dataset = entity_data; }

/*	Inventory doesn't instantiate with items right now							*/

/*	Will construct entities directly inside of the GameData. This is so that items
*	insantiated first can be reference by other entities who's inventories contain
*	them during component construction.											*/
void EntityFactory::constructEntities() {
	if (!_raw_entity_dataset.empty()) {
		for (std::vector<std::string> entity_save : _raw_entity_dataset) {
			Entity* new_entity = createEntity(entity_save);
			_game_data->entities.insert(_game_data->entities.end(), 
				{ new_entity->getID(), new_entity});
		}
	}
}