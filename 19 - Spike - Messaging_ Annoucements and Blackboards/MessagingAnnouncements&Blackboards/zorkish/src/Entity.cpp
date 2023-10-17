#include "../hdr/Entity.h"

/******************************************************************************
*							    De/Constructors
******************************************************************************/
Entity::Entity(std::string id, EntityTag tag) : _id(id), _tag(tag) { }


/******************************************************************************
*							Properties and Methods
******************************************************************************/
EntityTag Entity::getTag() { return _tag; }
std::string Entity::getID() { return _id; }

void Entity::setTag(EntityTag tag) { _tag = tag; }
