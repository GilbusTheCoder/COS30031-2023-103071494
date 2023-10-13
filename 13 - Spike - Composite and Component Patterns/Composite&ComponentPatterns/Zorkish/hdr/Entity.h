#include <string>
#include <vector>

#pragma once
enum class EntityTag {
	E_INVALID,
	E_TEST_ENTITY,
	E_PLAYER,
	E_LOCATION,
	E_CURRENT_LOCATION,
	E_ITEM,				// Technically doesn't need to exist but i don't like players putting
};						// kiddy pools in their backpacks.

class Entity {
private:
	std::string _id;
	EntityTag _tag = EntityTag::E_INVALID;

public:
	Entity(std::string id, EntityTag tag);

	EntityTag getTag();
	std::string getID();
	void setTag(EntityTag tag);
};

