#include <string>
#include <vector>

#pragma once
enum class EntityTag {
	INVALID,
	TEST_ENTITY,
	PLAYER,
	LOCATION,
	CURRENT_LOCATION,
	ITEM,				// Technically doesn't need to exist but i don't like players putting
};						// kiddy pools in their backpacks.

class Entity {
private:
	std::string _id;
	EntityTag _tag = EntityTag::INVALID;

public:
	Entity(std::string id, EntityTag tag);

	EntityTag getTag();
	std::string getID();
	void setTag(EntityTag tag);
};

