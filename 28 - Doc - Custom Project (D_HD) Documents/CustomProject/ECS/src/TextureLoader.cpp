#include "../hdr/TextureLoader.h"
#include "../../Game/hdr/SpriteLoader.h"

ECS::Texture ECS::TextureLoader::loadTextureComp(GameData* game_data, std::string comp_id,
	std::vector<std::string> component_args, ECS::sprite_map* sprites) {	
	Texture texture = {
		comp_id,
		C_TEXTURE,

		sprites->at(component_args[0]),
		determineBounds(game_data, comp_id, component_args[1]),
		determineRenderState(component_args[2]),
	};

	return texture;
}

/*	If we make some assumptions about the system this process is alot 
*	easier and since it's my system i'm going to make whatever fucking 
*	assumptions I want... now, assume entities have only 1 transform.
* 
*	YAY!! assumption made!! we can now search for "UEID+a" in the transform
*	map and find what we need. Now if for some reason we want something to
*	dynamically grow and shrink, we can give each texture it's own transform
*	and disallow save file instantiation of the transform (i dont like this
*	because it leads to unneccessary transforms). But if we did this then we
*	could just use the textures id to look up it's transform in the transform
*	map which is a neat lil hackery doo.				Feelin deranged rn...	*/
SDL_Rect ECS::TextureLoader::determineBounds(GameData* game_data, 
	component_id id, std::string unfmt_bounds) {
	if (unfmt_bounds == "transform" || unfmt_bounds == "t") {
		SDL_Rect bounds = game_data->transforms[TransUCIDFromID(id)].bounds;
		return bounds;
	}
	else {
		SDL_Rect bounds;

		std::vector<std::string> str_bound_values = splitSaveLine(unfmt_bounds, ',');
		for (int idx = 0; idx < 4; ++idx) {
			int bound = stoi(str_bound_values[idx]);

			switch (idx) {
			case 0:
				bounds.x = bound;
				break;
			case 1:
				bounds.y = bound;
				break;
			case 2:
				bounds.w = bound;
				break;
			case 3:
				bounds.h = bound;
				break;
			default:
				break;
			}

		}

		return bounds;
	}
}

bool ECS::TextureLoader::determineRenderState(std::string unfmt_render_state) {
	if (unfmt_render_state == "1" || unfmt_render_state == "true") {
		return true; }
	return false;
}

ECS::entity_id ECS::TextureLoader::TransUCIDFromID(component_id this_id) {
	if (this_id == "Aa") return this_id;

	entity_id ueid;
	component_id ucid = this_id;
	for (int id_it = 0; id_it != ucid.size(); ++id_it) {
		if (ucid[id_it] >= 97 && ucid[id_it] <= 122) {
			ueid = ucid.substr(0, id_it);
			ucid = ueid.append("a");
			return ucid;
		}
	}

	return ueid;
}
