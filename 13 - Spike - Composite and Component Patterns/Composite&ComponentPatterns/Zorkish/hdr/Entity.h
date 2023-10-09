#include <string>
#include <vector>

#include "../../Components/hdr/Component.h"

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
	int _id;
	
	EntityTag _tag = EntityTag::INVALID;

public:
	Entity(int id, EntityTag tag);

	EntityTag getTag();
	int getID();
	void setTag(EntityTag tag);
};

