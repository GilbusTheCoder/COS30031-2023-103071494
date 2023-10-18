#include "../hdr/EventDispatcher.h"

/******************************************************************************
*							    De/Constructors
******************************************************************************/
EventDispatcher::EventDispatcher(std::vector<Component*> init_components) {
	if (!init_components.empty()) {
		_local_components = init_components; }
	
	_move_command = new MoveCommand();
	_take_command = new TakeCommand();
	_look_command = new LookCommand();
	_show_command = new ShowCommand();
	_quit_command = new QuitCommand();
}

EventDispatcher::~EventDispatcher() {
	delete _move_command;
	delete _take_command;
	delete _look_command;
	delete _show_command;
	delete _quit_command;

	_move_command = nullptr;
	_take_command = nullptr;
	_look_command = nullptr;
	_show_command = nullptr;
	_quit_command = nullptr;
}



/******************************************************************************
*									Public
******************************************************************************/
void EventDispatcher::filterLocalComponents(GameData* game_data) {
	const char player = game_data->player[0];
	const char current_loc = game_data->current_location[0];

	if (!_local_components.empty()) {
		_local_components.clear();
		_local_components.shrink_to_fit(); }

	std::vector<Component*> entity_comps = getEntityComponents(player, game_data);
	std::vector<Component*> current_location_comps 
		= getEntityComponents(current_loc, game_data);
	
	_local_components.insert(_local_components.end(),
		entity_comps.begin(), entity_comps.end());
	_local_components.insert(_local_components.end(), 
		current_location_comps.begin(), current_location_comps.end());

	if (!_local_components.empty()) {
		game_data->reinstance_local_entity_cache = false; }
}

void EventDispatcher::addComponent(Component* component, 
	std::vector<Component*> components) {
	// Only cares about if there's a component or set, not neither nor both.
	if (component != nullptr && components.empty()) {
		_local_components.emplace_back(component); }
	else if (component == nullptr && !components.empty()) {
		for (Component* component : components) {
			_local_components.emplace_back(component); }
	}
}

void EventDispatcher::removeComponent(Component* component) {
	std::vector<Component*>::iterator traversal_it;
	
	for (traversal_it = _local_components.begin();
		traversal_it != _local_components.end(); ++traversal_it) {
		if ((*traversal_it) == component) {
			_local_components.erase(traversal_it);
			_local_components.shrink_to_fit(); }
	}
}

void EventDispatcher::resetComponents() {
	_local_components.clear();
	_local_components.shrink_to_fit();
}

// Using the input data, go through the commands and queue they're onEvent Methods()
/*	Commands are in order {move, take, look, show, quit} could us a map but meh		*/
std::queue<Command*> EventDispatcher::processEvents(
	GameData* game_data, InputData* input_data) 
{
	std::queue<Command*> events;
	CommandType c_type = input_data->c_type;

	switch (c_type) {
	case CommandType::MOVE:{
		std::string dir = getExitUEIDFromDir(input_data->_args[0]);

		if (!dir.empty()) {
			_move_command->setData(game_data, getExitUEIDFromDir(dir));
			events.push(_move_command); }

		break;
	}
	case CommandType::TAKE :
		break;
	case CommandType::LOOK :
		break;
	case CommandType::SHOW :
		break;
	case CommandType::QUIT :
		break;
	}

	return events;
}



/******************************************************************************
*								   Private
******************************************************************************/
std::vector<Component*> EventDispatcher::getEntityComponents(const char UEID,
	GameData* game_data) {
	std::vector<Component*> entity_comps;

	// Get all our pointers
	C_Render* renderer = getRenderer(UEID, game_data);
	C_Inventory* inventory = getInventory(UEID, game_data);
	std::vector<C_Portal*> portals = getPortals(UEID, game_data);

	entity_comps.emplace_back(renderer);
	entity_comps.emplace_back(inventory);

	// Cache all of our items and their renderers
	for (std::string Item_UEID : inventory->held_item_UEIDs) {
		C_Render* item_renderer = getRenderer(Item_UEID[0], game_data);
		entity_comps.emplace_back(item_renderer);
	}

	// Check for associated portals
	for (C_Portal* portal : portals) { entity_comps.emplace_back(portal); }
	

	return entity_comps;
}

C_Render* EventDispatcher::getRenderer(const char UEID, GameData* game_data) {	
	// Check for an associated renderer
	for (auto it = game_data->c_renderers.begin();
		it != game_data->c_renderers.end(); ++it) {
		if (it->first.front() == UEID) {
			return it->second; }
	}

	return nullptr;
}

C_Inventory* EventDispatcher::getInventory(const char UEID, GameData* game_data) {
	// Check for an associated inventory
	for (auto it = game_data->c_inventories.begin();
		it != game_data->c_inventories.end(); ++it) {
		if (it->first.front() == UEID) {
			return it->second; }
	}

	return nullptr;
}

std::vector<C_Portal*> EventDispatcher::getPortals(const char UEID, 
	GameData* game_data) {
	std::vector<C_Portal*> portals;

	// Check for an associated inventory
	for (auto it = game_data->c_portals.begin();
		it != game_data->c_portals.end(); ++it) {
		if (it->first.front() == UEID) {
			portals.emplace_back(it->second);
		}
	}

	return portals;
}

std::string EventDispatcher::getExitUEIDFromDir(std::string direction) { 
	for (Component* component : _local_components) {
		if (component->getFlag() == ComponentFlag::C_PORTAL) {
			std::vector<std::string> portal_info = component->getInfo();
			std::vector<std::string>::iterator traversal_it;

			for (traversal_it = portal_info.begin();
				traversal_it != portal_info.end(); ++traversal_it){
				if (*traversal_it == direction) {
					return *(traversal_it + 1);
				}
			}
		}
	}

	return "";
}

