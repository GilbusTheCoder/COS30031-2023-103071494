#include "CompLoader.h"
#include "../../Game/hdr/GameData.h"
#include <map>

#pragma once
/*	Call spriteloader to get all of our sprites
*	Read texture data from a file and assign, id, type, bounds and such
*	Create a map of texture components for use in GameData */

namespace ECS {
	typedef std::map<std::string, SDL_Texture*> sprite_map;

	class TextureLoader : public CompLoader {
	public:
		static Texture loadTextureComp(GameData* game_data, std::string comp_id,
			std::vector<std::string> component_args, sprite_map* sprites);
		
	private:
		static SDL_Rect determineBounds(GameData* game_data, component_id id, std::string unfmt_bounds);
		static bool determineRenderState(std::string unfmt_render_state);
		static entity_id transformUCIDFromID(component_id this_id);
	};
}
