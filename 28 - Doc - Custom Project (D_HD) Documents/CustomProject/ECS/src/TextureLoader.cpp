#include "../hdr/TextureLoader.h"
#include "../../Game/hdr/SpriteLoader.h"

ECS::Texture ECS::TextureLoader::loadTextureComp(std::string comp_id,
	std::vector<std::string> component_args, ECS::sprite_map* sprites) {	
	Texture texture = {
		comp_id,
		C_TEXTURE,

		sprites->at(component_args[0]),
		determineBounds(component_args[1]),
		determineRenderState(component_args[2]),
	};

	return texture;
}


SDL_Rect ECS::TextureLoader::determineBounds(std::string unfmt_bounds) {
	SDL_Rect bounds;

	std::vector<std::string> str_bound_values = splitSaveLine(unfmt_bounds, ',');
	for (int idx = 0; idx < 4; ++idx) {int bound = stoi(str_bound_values[idx]);
		
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
			break;	}

	}

	return bounds;
}

bool ECS::TextureLoader::determineRenderState(std::string unfmt_render_state) {
	if (unfmt_render_state == "1" || unfmt_render_state == "true") {
		return true; }
	return false;
}
