#include "Component.h"
#include "../../Zorkish/hdr/Entity.h"

#pragma once
class C_Portal : public Component {
private:
	std::string _entity_id;
	ComponentFlag _flag = ComponentFlag::PORTAL;
	
	std::string _dir;
	Entity* _exit = nullptr;
	// bool _is_locked = false;		Example of future functionality

public:
	C_Portal(std::string owning_entity_id, std::string direction, 
		Entity* exit = nullptr);

	ComponentFlag getFlag() override;
	std::string getDirection();
	Entity* getExit();

	void setExit(Entity* exit);

	void update() override;
	void render() override;
};

