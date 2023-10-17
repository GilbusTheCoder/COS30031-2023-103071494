#include <string>

#pragma once
enum class ComponentFlag {
	C_INVALID,
	C_RENDER,
	C_INVENTORY,
	C_PORTAL,
};

/*	Future optimizations could include allowing the components to know which
*	Entity they're associated with. This could trigger flags if the entity has
*	been manipulated and only entites which have been flagged via command will
*	be updated and rendered to the user.									*/
class Component {
public:
	virtual ComponentFlag getFlag() = 0;

	virtual void update() = 0;
	virtual void render() = 0;
};

