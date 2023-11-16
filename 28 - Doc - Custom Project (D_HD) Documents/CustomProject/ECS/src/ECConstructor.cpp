#include "../hdr/ECConstructor.h"
#include "../hdr/TransformLoader.h"
#include "../hdr/TextureLoader.h"
#include "../hdr/TagLoader.h"
#include "../../Game/hdr/SpriteLoader.h"

void ECS::ECConstructor::initGameObjects(GameData* game_data, SDL_Renderer* renderer,
	const std::string& entity_data_path, const std::string& sprites_filepath) {
	// OH YEAH WE'RE FUCKIN DOING IT
	auto sprites = Game::SpriteLoader::loadSprites(sprites_filepath, renderer);
	typed_ec3d fmt_entt_data = generateCTypeList( splitComponentDatum(splitComponentData(getRawEntityData(entity_data_path))));

	static int entity_count = 0;
	for (typed_ec2d entity : fmt_entt_data) {
		createEntity(game_data, renderer, &sprites, entity_count, entity);
		++entity_count;
	}
}


/*	Given the C_Texture_Data.txt file and can get chunks of entity data. Each entity block is
*	contained within an element of the returned vector									*/
std::vector<ECS::raw_entt> ECS::ECConstructor::getRawEntityData(const std::string& filepath) {
	std::ifstream reader = setSaveFile(filepath);
	bool in_entity_block = false;
	std::vector<raw_entt> entity_data;
	raw_entt entity_datum;
	std::string component_data;

	if (!reader.is_open()) {
		SDL_Log("ECConstructor >> Bad entity data filepath provided\n");
		return entity_data;
	}

	while (std::getline(reader, component_data)) {
		if (!isComment(component_data) && !component_data.empty()) {
			//	Remove all whitespaces and convert to lower, note that removing whitespace
			//	in this fashion leaves trailing garbage behind the comp_data.
			std::remove(component_data.begin(), component_data.end(), ' ');
			std::remove(component_data.begin(), component_data.end(), '\t');
			component_data = toLower(component_data);

			if (in_entity_block) {
				for (int idx = 0; idx <= component_data.size(); ++idx) {
					if (component_data[idx] == ';') {
						component_data = component_data.substr(0, idx + 1);
						entity_datum.append(component_data);
						break;
					} else if (component_data[idx] == '}') {
						in_entity_block = false;
						entity_datum.append(component_data.substr(0, idx));
						entity_data.emplace_back(entity_datum);
						entity_datum.clear();
						break;
					}
				}
			} else {
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

ECS::ec2d ECS::ECConstructor::splitComponentData(ec1d raw_entities) {
	ec2d ec_data;
	for (auto entity_data_chunk : raw_entities) {
		std::vector<raw_comp_data> comp_data = splitSaveLine(entity_data_chunk, ';');
		ec_data.emplace_back(comp_data);
	}

	return ec_data;
}

ECS::ec3d ECS::ECConstructor::splitComponentDatum(ec2d comp_data) {
	ec3d all_entt_args;
	for (std::vector<raw_comp_data> comp_set : comp_data) {
		std::vector<std::vector<raw_comp_arg>> comp_arg_set;
		for (raw_comp_data component : comp_set) {
			std::vector<raw_comp_arg> comp_args = splitSaveLine(component, '|');

			comp_arg_set.emplace_back(comp_args);
		}

		all_entt_args.emplace_back(comp_arg_set);
	}

	return all_entt_args;
}

void ECS::ECConstructor::createEntity(GameData* game_data, SDL_Renderer* renderer, 
	std::map<std::string, SDL_Texture*>* sprites, int entt_num, typed_ec2d ec_data) {
	Entity entt = { generateUEID(entt_num) };
	ComponentType prev_type = C_INVALID;

	int comp_count = 0;
	for (typed_comp_data comp : ec_data) {
		ComponentType type = std::get<0>(comp);
		std::vector<raw_comp_arg> args = std::get<1>(comp);

		if (type == prev_type) ++comp_count;
		else comp_count = 0;

		CompData comp_data = {
			game_data,
			renderer,
			sprites,

			generateUCID(entt.id, comp_count),
			type,
			args,
		};

		createComponent(comp_data);

		prev_type = type;
	}

	game_data->entities.insert({ entt.id, entt });
}

void ECS::ECConstructor::createComponent(CompData init_data) {
	/*	Food for thought... if this switch was ordered from the densest data
	*	structure to the sparsest(?), I'd be able to infer component data
	*	from the others.
	* 
	*	E.g. if texture is first, then if the transform and / origin components
	*	are listed and have no data associated with them. This data can be
	*	taken from the texture component which belongs to the entt.		*/
	
	
	switch (init_data.type) {
	case C_TRANSFORM: {
		ECS::Transform transform = ECS::TransformLoader::loadTransformComponent(init_data.id, init_data.args[0]);
		init_data.game_data->transforms.insert({ transform.id, transform });
		return; }
	case C_TEXTURE: {
		ECS::Texture texture = ECS::TextureLoader::loadTextureComp(init_data.game_data, init_data.id, init_data.args, init_data.sprites);
		init_data.game_data->textures.insert({ texture.id, texture });
		return; }
	case C_UILABEL:
		return;
	case C_INTERACTABLE:
		return;
	case C_MOVABLE:
		return;
	case C_TAG:{
		ECS::Tag tag = ECS::TagLoader::loadTagComponent(init_data.id, init_data.args[0]);
		init_data.game_data->tags.insert({ tag.id, tag });
		return;	}
	case C_INVALID:
		return;
	}
}


ECS::entity_id ECS::ECConstructor::generateUEID(int entity_count) {
	entity_id e_id;
	const int ascii_offset = 65;
	const int alph_len = 25;
	int ueid_len = determineUEIDLen(entity_count);
	if (ueid_len < 1) { return e_id; }
	
	switch (ueid_len) {
	case 1: {
		entity_id id(1, entity_count + ascii_offset);
		return id; }
	
	case 2: {
		entity_id second(1, (entity_count % alph_len) + ascii_offset - 1);
		entity_id first(1, int(floor(entity_count / alph_len)) + ascii_offset - 1);
		
		e_id.append(first);
		e_id.append(second);

		return e_id; }
	
	case 3: {
		int second_value = int(floor(entity_count / alph_len));

		entity_id third(1, (entity_count % alph_len) + ascii_offset);
		entity_id second(1, int(floor(entity_count / alph_len)) + ascii_offset);
		entity_id first(1, int(floor(entity_count / second_value)) + ascii_offset);

		e_id.append(first);
		e_id.append(second);
		e_id.append(third);

		return e_id; }
	
	case 4: {
		int third_value = int(floor(entity_count / alph_len));
		int second_value = int(floor(entity_count / third_value));
		
		entity_id fourth(1, (entity_count % alph_len) + ascii_offset);
		entity_id third(1, int(floor(entity_count / alph_len)) + ascii_offset);
		entity_id second(1, int(floor(entity_count / third_value)) + ascii_offset);
		entity_id first(1, int(floor(entity_count / second_value)) + ascii_offset);

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
	const int alph_len = 25;
	const int ascii_offset = 97;
	int ueid_len = determineUEIDLen(component_count);
	if (ueid_len < 1) { return c_id; }

	switch (ueid_len) {
	case 1: {
		component_id c_id(1, component_count + ascii_offset);
		full_c_id.append(c_id);
		return full_c_id; }

	case 2: {
		component_id second(1, (component_count % alph_len) + ascii_offset);
		component_id first(1, int(floor(component_count / alph_len)) + ascii_offset);

		c_id.append(first);
		c_id.append(second);
		full_c_id.append(c_id);
	
		return full_c_id; }
	}
}

int ECS::ECConstructor::determineUEIDLen(int entity_count) {
	if (entity_count <= 25) { return 1; }
	else if (entity_count <= 675) { return 2; }
	else if (entity_count <= 17575) { return 3; }
	else if (entity_count <= 456975) { return 4; }
	else { return -1; }
}

ECS::ComponentType ECS::ECConstructor::determineCType(raw_comp_arg raw_type) {
	if (raw_type == "transform") { return ComponentType::C_TRANSFORM; }
	else if (raw_type == "texture") { return ComponentType::C_TEXTURE; }
	else if (raw_type == "uilabel") { return ComponentType::C_UILABEL; }
	else if (raw_type == "interactable") { return ComponentType::C_INTERACTABLE; }
	else if (raw_type == "movable") { return ComponentType::C_MOVABLE; }
	else if (raw_type == "tag") { return ComponentType::C_TAG; }
	else { return ComponentType::C_INVALID; }
}

ECS::typed_ec3d ECS::ECConstructor::generateCTypeList(ec3d ec_data) {
	typed_ec3d typed_ec_data;

	for (auto entity : ec_data) {
		typed_ec2d typed_c_data;
		for (auto component : entity) {
			std::pair<ComponentType, std::vector<raw_comp_arg>> typed_arg_data;
			ComponentType type = determineCType(component[0]);
			if (type == C_INVALID) {
				SDL_Log("ECConstructor >> Couldn't instance type '%s'", component[0].c_str()); }

			component.erase(component.begin());
			component.shrink_to_fit();
			
			std::vector<raw_comp_arg> args = component;
			typed_arg_data = { type, args };

			typed_c_data.emplace_back(typed_arg_data); }
		typed_ec_data.emplace_back(typed_c_data);
	}
	
	return typed_ec_data;
}
