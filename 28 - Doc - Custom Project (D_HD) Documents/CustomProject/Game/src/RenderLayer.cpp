#include "../hdr/RenderLayer.h"

SDL_Renderer*  ECS::RenderLayer::_renderer = nullptr;


bool ECS::RenderLayer::init(SDL_Window* window, const RenderContext& context) {
	if (!window) {
		SDL_Log("RenderLayer >> No window context provided to layer\n");
		return false; }
	
	if (!_renderer) {
		_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if (!_renderer) {
			SDL_Log("RenderLayer >> Failed to instance renderer\n");
			return false; }	}

	setRenderContext(context);
	if (!_game_data_ref) { return false; }
	return true; }


void ECS::RenderLayer::destroy(bool destroy_SDL_renderer) {
	if (_game_data_ref) { _game_data_ref = nullptr; }
	if (destroy_SDL_renderer) { 
		SDL_DestroyRenderer(_renderer); 
		_renderer = nullptr; } }


void ECS::RenderLayer::render() {
	if (_game_data_ref && _renderer) {
		for (component_id texture_id : _layer_textures) {
			SDL_RenderCopy(_renderer, _game_data_ref->textures[texture_id].texture, 
				nullptr, &_game_data_ref->textures[texture_id].bounds);
		}
	} }


void ECS::RenderLayer::setRenderContext(const RenderContext& context) {
	_is_active = context.render_this;

	if (!context.game_data) {
		_layer_transforms = context.layer_transforms;
		_layer_textures = context.layer_textures;
		_layer_uilabels = context.layer_uilabels;
	} else {
		if (context.game_data) { _game_data_ref = context.game_data; }
		if (!context.render_filters.empty()) {
			/*	cycle through the game data's tag and pull out all the UCIDs
			*	with the associated tag
			*	Find the UEID and append 'a' to it (starting iterator for comp map)
			*	Cycle through comp map and copy the data to the layer data while
			*	the prefix remains the same.									*/
			std::vector<ComponentType> c_types = { C_TRANSFORM, C_TEXTURE, C_UILABEL };
			for (EntityTag tag : context.render_filters) {
				for (auto c_tag : context.game_data->tags) {
					if (tag == c_tag.second.tag) {
						for (ComponentType type : c_types) {
							entity_id ueid = UEIDfromUCID(c_tag.second.id);
							getTaggedComponentsFromUEID(ueid, type); }
					}
				}
			}
		}
	} }


void ECS::RenderLayer::getTaggedComponentsFromUEID(entity_id ueid, 
	ComponentType type) {
	component_id c_ueid = ueid;
	
	if (!_game_data_ref) {
		SDL_Log("RenderLayer >> No gamedata context was provided before tagged component id instantiation\n"); }
	
	switch (type) {
	case C_TRANSFORM: {
		component_id ucid = ueid;
		ucid.append("a");
		_layer_transforms.emplace_back(ucid);
		break; }

	case C_TEXTURE: {
		entity_id c_ueid = ueid;

		for (auto texture : _game_data_ref->textures) {
			if (UEIDfromUCID(texture.second.id) == c_ueid) {
				_layer_textures.emplace_back(texture.second.id); }
		} break; }

	case C_UILABEL: {
		entity_id ucid = ueid;
		ucid.append("a");

		for (auto label : _game_data_ref->labels) {
			if (ucid == label.second.id) {
				_layer_uilabels.emplace_back(label.second.id); }
		} break; }

	default:
		break; } }


ECS::entity_id ECS::RenderLayer::UEIDfromUCID(component_id this_id) {
	entity_id ueid;
	component_id ucid = this_id;
	for (int id_it = 0; id_it != ucid.size(); ++id_it) {
		if (ucid[id_it] >= 97 && ucid[id_it] <= 122) {
			ueid = ucid.substr(0, id_it);
			return ueid;
		}
	}

	return ueid; }