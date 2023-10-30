#include "../hdr/EventDispatcher.h"

/******************************************************************************
*							    De/Constructors
******************************************************************************/
EventDispatcher::EventDispatcher() {
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
void EventDispatcher::setGameData(GameData* game_data) { 
	_game_data = game_data; }

void EventDispatcher::filterLocalComponents() {
	resetComponents();

	const char player = _game_data->player[0];
	const char current_loc = _game_data->current_location[0];

	getEntityComponents(player);
	getEntityComponents(current_loc);
}

void EventDispatcher::resetComponents() {
	if (!_game_data->_local_renderers.empty()) {
		_game_data->_local_renderers.clear(); }
	if (!_game_data->_local_inventories.empty()) {
		_game_data->_local_inventories.clear(); }
	if (!_game_data->_local_portals.empty()) {
		_game_data->_local_portals.clear(); }
}

//	Using the input data, go through the commands and queue they're onEvent Methods()
/*	Commands are in order {move, take, look, show, quit} could us a map but meh		*/
std::queue<Command*> EventDispatcher::processEvents(InputData* input_data) {
	std::queue<Command*> events;
	InputData* c_input = input_data;
	CommandType c_type = c_input->c_type;

	switch (c_type) {
	case CommandType::MOVE:{
		std::string exit_UEID = getExitUEIDFromDir(c_input->args[0]);

		if (!exit_UEID.empty()) {
			_move_command->setData(_game_data, exit_UEID);
			events.push(_move_command); 
		} break;
	}
	
	case CommandType::TAKE :
		_take_command->setData(c_input->src, c_input->dest, c_input->item);
		events.push(_take_command);
		break;

	// Expects input data args in form {<around> || <at, "x"> || <at, "x", in, "y">}
	case CommandType::LOOK: 
		_look_command->setData(_game_data, c_input);
		events.push(_look_command);
		break;
	
	case CommandType::SHOW :
		_show_command->setData(_game_data, c_input->args[0]);
		events.push(_show_command);
		break;
	
	case CommandType::QUIT :
		_quit_command->setData(_game_data);
		events.push(_quit_command);
		break;
	}

	return events;
}


/******************************************************************************
*								   Private
******************************************************************************/
void EventDispatcher::getEntityComponents(const char UEID) 
{	// Get all our pointers
	C_Render* renderer = getRenderer(UEID);
	C_Inventory* inventory = getInventory(UEID);
	std::vector<C_Portal*> portals = getPortals(UEID);

	_game_data->_local_renderers.emplace_back(getRenderer(UEID));
	_game_data->_local_inventories.emplace_back(getInventory(UEID));
	
	for (C_Portal* portal : portals) {
		_game_data->_local_portals.emplace_back(portal); 
	}	portals.clear();

	// Cache all of our items and their renderers
	for (std::string Item_UEID : inventory->held_item_UEIDs) {
		C_Render* item_renderer = getRenderer(Item_UEID[0]);
		_game_data->_local_renderers.emplace_back(item_renderer);
	}
}


C_Render* EventDispatcher::getRenderer(const char UEID) {	
	// Check for an associated renderer
	for (auto it = _game_data->c_renderers.begin();
		it != _game_data->c_renderers.end(); ++it) {
		if (it->first.front() == UEID) {
			return it->second; }
	}

	return nullptr;
}

C_Inventory* EventDispatcher::getInventory(const char UEID) {
	// Check for an associated inventory
	for (auto it = _game_data->c_inventories.begin();
		it != _game_data->c_inventories.end(); ++it) {
		if (it->first.front() == UEID) {
			return it->second; }
	}

	return nullptr;
}

std::vector<C_Portal*> EventDispatcher::getPortals(const char UEID) {
	std::vector<C_Portal*> portals;

	// Check for an associated inventory
	for (auto it = _game_data->c_portals.begin();
		it != _game_data->c_portals.end(); ++it) {
		if (it->first.front() == UEID) {
			portals.emplace_back(it->second);
		}
	}

	return portals;
}

std::string EventDispatcher::getExitUEIDFromDir(std::string direction) { 
	for (C_Portal* portal : _game_data->_local_portals) {
		//	Returns {dir, UEID, dir, UEID, ...}
		std::vector<std::string> portal_info = portal->getInfo();
		std::vector<std::string>::iterator traversal_it;
		
		for (traversal_it = portal_info.begin();
			traversal_it != portal_info.end(); ++traversal_it){
			if (*traversal_it == direction) {
				return *(traversal_it + 1);	// return the exits UEID
			}
		}
	}

	return "";
}

