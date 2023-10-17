/*	Will take a set of semi-formatted data from the world loader in order to
*	instantiate new entities, it will return a vector of entities			  */

#include "Entity.h"
#include "GameData.h"
#include "ComponentFactory.h"

#pragma once
/*	Expects data as lowercase strings in the form:
*	   <<EntityTag0, ComponentFlag0(arg0,arg1)|...|ComponentFlagN(arg0,arg1)>,
*	    <EntityTag1, ComponentFlag0(arg0,arg1)|...|ComponentFlagN(arg0,arg1)>,
*		<...>,
*		<EntityTagN, ComponentFlag0(arg0,arg1)|...|ComponentFlagN(arg0,arg1)>>
*																			  */
class EntityFactory {
private:
	std::vector<std::vector<std::string>> _raw_entity_dataset;
	GameData* _game_data = nullptr;
	ComponentFactory* _component_factory = nullptr;

	EntityTag determineTag(std::string tag);
	std::vector<std::string> splitSaveLine(std::string& line, const char delimiter);
	std::string generateUEID(int entity_num);
	Entity* createEntity(int entity_num, std::vector<std::string> entity_data);
	void setEntityRefs(std::string entity_id, std::vector<std::string> entity_data);

public:
	EntityFactory(GameData* game_data = nullptr,
		std::vector<std::vector<std::string>> entity_data = {});
	~EntityFactory();

	void setEntityData(std::vector<std::vector<std::string>> entity_data);
	void constructEntities();
};