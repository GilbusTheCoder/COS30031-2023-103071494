#include "GameData.h"
#include "../../ECS/hdr/Component.h"
#include <SDL_render.h>
#include <vector>	

#pragma once
/*	LAYERED RENDERING!!! This is a system which belongs to the ECS
*	each layer knows which textures and transform it needs and
*	can toggle the render_this bool for each texture in it's 
*	list.													
*
*	A RenderLayer can be told which textures it needs to care about 
*	using a tag or it can be fed textures manually. This is basically
*	how im building the UI system.									*/

namespace ECS {
	typedef std::map<component_id, Texture>::iterator text_it;
	typedef std::map<component_id, UILabel>::iterator label_it;
	typedef std::map<component_id, Transform>::iterator trans_it;

	struct RenderContext {
		GameData* game_data = nullptr;
		std::vector<EntityTag> render_filters;

		std::vector<component_id> layer_transforms;
		std::vector<component_id> layer_textures;
		std::vector<component_id> layer_uilabels;
	};

	class RenderLayer {
	private:
		static  SDL_Renderer* _renderer;
		GameData* _game_data_ref = nullptr;
		bool _is_active = false;

		std::vector<component_id> _layer_transforms;
		std::vector<component_id> _layer_textures;
		std::vector<component_id> _layer_uilabels;

	public:
		bool init(SDL_Window* window, const RenderContext& context);
		void destroy(bool destroy_SDL_renderer=false);
		void update();
		void render();

		inline SDL_Renderer* getRenderer() { return _renderer; }
		const inline bool isActive() { return _is_active; }

		void setRenderContext(const RenderContext& context);
	
	private:
		void getTaggedComponentsFromUEID(entity_id ueid, ComponentType type);
		entity_id UEIDfromUCID(component_id this_id);
		component_id CIDfromUCID(component_id this_id);
	};
}
