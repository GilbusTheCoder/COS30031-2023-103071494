#include "Component.h"
#include "../../Zorkish/hdr/Entity.h"

#pragma once
class C_Portal : public Component {
private:
	std::string _entity_id;
	Entity* _exit = nullptr;
	// bool _is_locked = false;		Example of future functionality addons

public:
	C_Portal(std::string owning_entity_id, Entity* exit = nullptr);

	void setExit(Entity* exit);
	Entity* getExit();
};

