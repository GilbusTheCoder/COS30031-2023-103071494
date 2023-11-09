#include "../../ECS/hdr/Component.h"
#include "../../ECS/hdr/Entity.h"
#include <map>

#pragma once
namespace ECS {

	struct GameData {
		std::map<entity_id, Entity> entities;

		std::map<component_id, Transform> transforms;
		std::map<component_id, Origin> origins;
		std::map<component_id, Texture> textures;
		std::map<component_id, UILabel> labels;
		std::map<component_id, Interactable> interactables;
		std::map<component_id, Movable> movables;
	};
}