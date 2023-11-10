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

	setRenderContext(context); }


void ECS::RenderLayer::setRenderContext(const RenderContext& context) {
	if (!context.game_data) {
		_layer_transforms = context.layer_transforms;
		_layer_textures = context.layer_textures;
		_layer_uilabels = context.layer_uilabels;
	} else {
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
							getComponentsFromTag(context.game_data, tag, type); }
					}
				}
			}
		} else {
			SDL_Log("RenderLayer >> RenderContext.game_data was provided by no render_filters\n");
		}
	} }


void ECS::RenderLayer::getComponentsFromTag(ECS::GameData* game_data, 
	ECS::EntityTag tag, const ECS::ComponentType type_filter) {
	comp_traversal_data traversal_data;
	std::vector<Tag> relevant_tags;
	for (auto e_tag : game_data->tags) {
		if (e_tag.second.tag == tag) {
			relevant_tags.emplace_back(e_tag.second); } }

	for (Tag tag : relevant_tags) {
		traversal_data = traversalDataFromUCID(game_data, type_filter, tag.id);

		switch (tag.tag) {
		case C_TRANSFORM:
			getLayerTransforms(game_data, traversal_data);
			break;
		case C_TEXTURE:
			getLayerTextures(game_data, traversal_data);
			break;
		case C_UILABEL:
			getLayerLabels(game_data, traversal_data);
			break;
		default:
			break;
		}

	} }


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

ECS::comp_traversal_data ECS::RenderLayer::traversalDataFromUCID(GameData* game_data,
	ComponentType map_filter, ECS::component_id this_id) {
	int start_idx=0, end_idx=0;
	comp_traversal_data offsets = {start_idx, end_idx};
	entity_id ueid;
	component_id ucid;

	if (this_id == "Aa") {
		ueid = "A";
		ucid = this_id; }
	else {
		ueid = UEIDfromUCID(this_id);
		ucid = ueid.append("a"); }

	switch (map_filter) {
	case C_TRANSFORM: {
		auto trans_it = game_data->transforms.begin();
		entity_id it_ueid;
		int idx = 0;

		for (trans_it; trans_it != game_data->transforms.end(); ++trans_it) {
			if (trans_it->first == ucid) { start_idx = idx; }
			
			it_ueid = UEIDfromUCID(trans_it->first);
			if (ueid == it_ueid) { end_idx = idx; return { start_idx, end_idx }; }
			
			// Checking if we're in range of our comp id's
			if (start_idx) { _layer_transforms.emplace_back(trans_it->first); }
			++idx;	}

		break;
	}
	case C_TEXTURE: {
		auto trans_it = game_data->textures.begin();
		entity_id it_ueid;
		int idx = 0;

		for (trans_it; trans_it != game_data->textures.end(); ++trans_it) {
			if (trans_it->first == ucid) { start_idx = idx; }

			it_ueid = UEIDfromUCID(trans_it->first);
			if (ueid == it_ueid) { end_idx = idx; return { start_idx, end_idx }; }

			if (start_idx) { _layer_textures.emplace_back(trans_it->first); }
			++idx; }

		break;
	}
	case C_UILABEL: {
		auto trans_it = game_data->labels.begin();
		entity_id it_ueid;
		int idx = 0;

		for (trans_it; trans_it != game_data->labels.end(); ++trans_it) {
			if (trans_it->first == ucid) { start_idx = idx; }

			it_ueid = UEIDfromUCID(trans_it->first);
			if (ueid == it_ueid) { end_idx = idx; return { start_idx, end_idx }; }

			if (start_idx) { _layer_uilabels.emplace_back(trans_it->first); }
			++idx; }

		break; }

	default: SDL_Log("RenderLayer >> ComponentType not renderables");
	} }


void ECS::RenderLayer::getLayerTransforms(GameData* game_data, 
	comp_traversal_data traversal_data) {
	int start_idx, end_idx;
	auto [start_idx, end_idx] = traversal_data;
	auto start_it=game_data->transforms.begin(), 
		end_it=game_data->transforms.end();

	
	for (int idx = 0; idx < start_idx; ++idx) { ++start_it; }
	end_it = start_it;

	for (int idx = start_idx; idx < end_idx; ++idx) { 
		_layer_transforms.emplace_back(end_it->first);
		++end_it; } }


void ECS::RenderLayer::getLayerTextures(GameData* game_data, 
	comp_traversal_data traversal_data) {
	int start_idx, end_idx;
	auto [start_idx, end_idx] = traversal_data;
	auto start_it = game_data->textures.begin(),
		end_it = game_data->textures.end();


	for (int idx = 0; idx < start_idx; ++idx) { ++start_it; }
	end_it = start_it;

	for (int idx = start_idx; idx < end_idx; ++idx) {
		_layer_textures.emplace_back(end_it->first);
		++end_it;
	} }


void ECS::RenderLayer::getLayerLabels(GameData* game_data, 
	comp_traversal_data traversal_data) {
	int start_idx, end_idx;
	auto [start_idx, end_idx] = traversal_data;
	auto start_it = game_data->labels.begin(),
		end_it = game_data->labels.end();


	for (int idx = 0; idx < start_idx; ++idx) { ++start_it; }
	end_it = start_it;

	for (int idx = start_idx; idx < end_idx; ++idx) {
		_layer_uilabels.emplace_back(end_it->first);
		++end_it;
	} }

