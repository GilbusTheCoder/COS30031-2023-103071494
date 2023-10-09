#include "../hdr/Entity.h"


/******************************************************************************
*							    De/Constructors
******************************************************************************/
Entity::Entity(int id, EntityTag tag) : _id(id), _tag(tag) { }


/******************************************************************************
*							Properties and Methods
******************************************************************************/
EntityTag Entity::getTag() { return EntityTag(); }
int Entity::getID() { return _id; }

void Entity::setTag(EntityTag tag) { _tag = tag; }
