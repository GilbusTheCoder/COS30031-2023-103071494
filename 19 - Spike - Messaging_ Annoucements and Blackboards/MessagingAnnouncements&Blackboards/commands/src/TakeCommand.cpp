#include "../hdr/TakeCommand.h"

TakeCommand::TakeCommand() { }

void TakeCommand::setData(C_Inventory* source, C_Inventory* dest, Entity* item) {
	_source = source;
	_dest = dest;
	_item = item;
}

void TakeCommand::triggerEvent() {
	_dest->addItem(_item);
	_source->deleteItem(_item);
}

