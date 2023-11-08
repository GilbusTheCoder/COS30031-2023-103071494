#pragma once
#include "../../Game/hdr/FileReader.h"
#include "../../Game/hdr/GameData.h"

namespace ECS {
	typedef std::string raw_entt, raw_comp_data, raw_comp_datum;

	class ECConstructor : public Game::FileReader {
	public:
		static GameData* initGameData();
		static void initGameObjects(GameData* game_data, const std::string& entity_data_path,
			const std::string& sprites_filepath);
		
	private:
		static std::vector<raw_entt> getRawEntityData(const std::string& filepath);

		static std::map<entity_id, Entity> initEntities(const std::string& entity_data_path);
		static void initEntitiesComponents(entity_id owners_id, std::vector<raw_comp_datum> c_data);

		static std::pair<entity_id, Entity> initEntity(int entity_count);
		static std::pair<component_id, Component> initComponent(int component_count, 
			entity_id owning_id, ComponentType type, std::vector<raw_comp_datum> c_data);
	
		static entity_id generateUEID(int entity_count);
		static component_id generateUCID(entity_id owners_id, int component_count);
		static int determineUEIDLen(int entity_count);

		static ComponentType determineCType(raw_comp_datum raw_type);
	};
}