#include "Component.h"
#include "../../Zorkish/hdr/Entity.h"

#pragma once
class C_Portal : public Component {
private:
	std::string _ucid;
	ComponentFlag _flag = ComponentFlag::C_PORTAL;

	std::string _dir;
	Entity* _exit = nullptr;
	// bool _is_locked = false;		Example of future functionality

public:
	C_Portal(std::string ucid, std::string direction,
		Entity* exit = nullptr);

	std::string getUCID();
	ComponentFlag getFlag() override;
	std::string getDirection();
	Entity* getExit();

	void setExit(Entity* exit);

	void onEvent() override;
	std::vector<std::string> getInfo() override;
};

