#include "Command.h"

#pragma once
class TakeCommand : virtual public Command {
private:
	C_Inventory* _source = nullptr;
	C_Inventory* _dest = nullptr;
	Entity* _item = nullptr;

public:
	TakeCommand();

	void setData(C_Inventory* source, C_Inventory* dest, Entity* item);
	void triggerEvent() override;
};

