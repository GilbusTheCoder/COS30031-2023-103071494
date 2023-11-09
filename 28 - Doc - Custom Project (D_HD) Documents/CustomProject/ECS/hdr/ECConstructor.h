#include "../../Game/hdr/FileReader.h"
#include "../../Game/hdr/GameData.h"
#pragma once
namespace ECS {
	/*	It looks alot worse without typedefs all over the shop. each alias is used contextually 
	*	based off how processed the data is. Think of it as each time we process the EC dataset
	*	we add an extra dimension to our EC Array.											*/
	typedef std::string raw_entt, raw_comp_data, raw_comp_arg;
	typedef std::pair<ComponentType, std::vector<raw_comp_arg>> typed_comp_data;

	typedef std::vector<raw_entt> ec1d;
	typedef std::vector<std::vector<raw_comp_data>> ec2d;
	typedef std::vector<std::vector<std::vector<raw_comp_arg>>> ec3d;

	typedef std::vector<std::pair<ComponentType, std::vector<raw_comp_arg>>> typed_ec2d;
	typedef std::vector<std::vector<std::pair<ComponentType, std::vector<raw_comp_arg>>>> typed_ec3d;

	struct CompData {
		GameData* game_data = nullptr;
		SDL_Renderer* renderer = nullptr;
		std::map<std::string, SDL_Texture*>* sprites = nullptr;

		component_id id = "zzzzzzzz";
		ComponentType type = C_INVALID;
		std::vector<raw_comp_arg> args = {};
	};

	class ECConstructor : public Game::FileReader {
	public:
		static void initGameObjects(GameData* game_data, SDL_Renderer* renderer, 
			const std::string& entity_data_path, const std::string& sprites_filepath);
		
	private:
		static ec1d getRawEntityData(const std::string& filepath);
		static ec2d splitComponentData(ec1d raw_entities);
		static ec3d splitComponentDatum(ec2d comp_data);

		static void createEntity(GameData* game_data, SDL_Renderer* renderer, 
			std::map<std::string, SDL_Texture*>* sprites, int entt_num, typed_ec2d ec_data);
		static void createComponent(CompData init_data);
	
		static entity_id generateUEID(int entity_count);
		static component_id generateUCID(entity_id owners_id, int component_count);
		static int determineUEIDLen(int entity_count);

		static ComponentType determineCType(raw_comp_arg raw_type);
		static typed_ec3d generateCTypeList(ec3d ec_data);
	};
}