#include <SDL_render.h>
#include <vector>	
#include "../../ECS/hdr/Component.h"

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
	struct RenderContext {
		std::vector<EntityTag> render_filters;

		std::vector<component_id> layer_transforms;
		std::vector<component_id> layer_textures;
		std::vector<component_id> layer_uilabels;
	};

	class RenderLayer {
	private:
		static  SDL_Renderer* _renderer;
		bool _is_active = false;

		std::vector<component_id> layer_transforms;
		std::vector<component_id> layer_textures;
		std::vector<component_id> layer_uilabels;

	public:
		bool init(SDL_Window* window);
		void destroy();
		void update();
		void render();
	
	private:
	
	};
}

