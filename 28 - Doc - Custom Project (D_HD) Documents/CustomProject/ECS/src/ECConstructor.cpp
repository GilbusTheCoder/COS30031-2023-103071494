#include "../hdr/ECConstructor.h"
#include <string>
#include <algorithm>

// Constructs our game data
ECS::GameData* ECS::ECConstructor::initGameData() {
	GameData* game_data = new GameData();
	int type = ECS::ComponentType::C_TRANSFORM;

	for (type; type != ECS::ComponentType::C_INVALID; ++type) {
		std::map<ECS::component_id, ECS::Component> component_set;
		std::map < ECS::ComponentType, std::map<ECS::component_id, ECS::Component>> component_type_set;

		component_type_set.insert( { ECS::ComponentType(type), component_set } );
	}

	return game_data;
}


/*	Given the C_Texture_Data.txt file and can get chunks of entity data. Each entity block is
*	contained within an element of the returned vector									*/
std::vector<ECS::raw_entt> ECS::ECConstructor::getRawEntityData(const std::string& filepath) {
	std::ifstream reader = setSaveFile(filepath);
	bool in_entity_block = false;
	std::vector<raw_entt> entity_data;
	raw_entt entity_datum;
	std::string component_data;

	while (std::getline(reader, component_data)) {
		if (!isComment(component_data) && !component_data.empty()) {
			if (in_entity_block) {
				for (int idx = 0; idx <= component_data.size(); ++idx) {
					if (component_data[idx] = '}') {
						in_entity_block = false;
						entity_datum.append(component_data);
						entity_data.emplace_back(entity_datum);
						break;
					}
				}

				entity_datum.append(component_data);

			}
			else {
				for (int idx = 0; idx <= component_data.size(); ++idx) {
					if (component_data[idx] == '{') {
						in_entity_block = true;
						break;
					}
				}
			}
		}
	}

	return entity_data;
}

std::pair<ECS::entity_id, ECS::Entity> ECS::ECConstructor::initEntity(int entity_count) {
	Entity new_entity;
	new_entity.id = generateUEID(entity_count);

	return { new_entity.id, new_entity };
}


ECS::entity_id ECS::ECConstructor::generateUEID(int entity_count) {
	entity_id e_id;
	const int alph_len = 26;
	int ueid_len = determineUEIDLen(entity_count);
	if (ueid_len < 1) { return e_id; }
	
	switch (ueid_len) {
	case 1: {
		entity_id id(1, entity_count + 65);
		return id; }
	
	case 2: {
		entity_id second(1, (entity_count % alph_len) + 65);
		entity_id first(1, int(floor(entity_count / alph_len)) + 65);
		
		e_id.append(first);
		e_id.append(second);

		return e_id; }
	
	case 3: {
		int second_value = int(floor(entity_count / alph_len));

		entity_id third(1, (entity_count % alph_len) + 65);
		entity_id second(1, int(floor(entity_count / alph_len)) + 65);
		entity_id first(1, int(floor(entity_count / second_value)) + 65);

		e_id.append(first);
		e_id.append(second);
		e_id.append(third);

		return e_id; }
	
	case 4: {
		int third_value = int(floor(entity_count / alph_len));
		int second_value = int(floor(entity_count / third_value));
		
		entity_id fourth(1, (entity_count % alph_len) + 65);
		entity_id third(1, int(floor(entity_count / alph_len)) + 65);
		entity_id second(1, int(floor(entity_count / third_value)) + 65);
		entity_id first(1, int(floor(entity_count / second_value)) + 65);

		e_id.append(first);
		e_id.append(second);
		e_id.append(third);
		e_id.append(fourth);

		return e_id; }
	default:
		return e_id;
	}
}

ECS::component_id ECS::ECConstructor::generateUCID(entity_id owners_id, int component_count) {
	component_id full_c_id = owners_id;
	component_id c_id;
	const int alph_len = 26;
	int ueid_len = determineUEIDLen(component_count);
	if (ueid_len < 1) { return c_id; }

	switch (ueid_len) {
	case 1: {
		component_id c_id(1, component_count + 65);
		full_c_id.append(c_id);
		return full_c_id; }

	case 2: {
		component_id second(1, (component_count % alph_len) + 65);
		component_id first(1, int(floor(component_count / alph_len)) + 65);

		c_id.append(first);
		c_id.append(second);
		full_c_id.append(c_id);
	
		return full_c_id; }
	}
}

int ECS::ECConstructor::determineUEIDLen(int entity_count) {
	if (entity_count <= 26) { return 1; }
	else if (entity_count <= 676) { return 2; }
	else if (entity_count <= 17576) { return 3; }
	else if (entity_count <= 456976) { return 4; }
	else { return -1; }
}

ECS::ComponentType ECS::ECConstructor::determineCType(raw_comp_datum raw_type) {
	if (raw_type == "transform") { return ComponentType::C_TRANSFORM; }
	else if (raw_type == "origin") { return ComponentType::C_ORIGIN; }
	else if (raw_type == "texture") { return ComponentType::C_TEXTURE; }
	else if (raw_type == "uilabel") { return ComponentType::C_UILABEL; }
	else if (raw_type == "interactable") { return ComponentType::C_INTERACTABLE; }
	else if (raw_type == "movable") { return ComponentType::C_MOVABLE; }
	else { return ComponentType::C_INVALID; }
}
