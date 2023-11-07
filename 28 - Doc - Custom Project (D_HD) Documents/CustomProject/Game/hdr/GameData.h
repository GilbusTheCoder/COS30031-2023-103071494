#include <map>

#include "../../ECS/hdr/Component.h"
#include "../../ECS/hdr/Entity.h"

#pragma once
namespace ECS {
	struct GameData {
		std::map<entity_id, Entity> entities;
		std::map<ComponentType, std::map<component_id, Component>> components;
	};
}