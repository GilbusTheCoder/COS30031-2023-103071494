#include "GameData.h"
#include "RenderLayer.h"

#pragma once
namespace Game {
	class Renderer {
	private:
		std::vector<ECS::RenderLayer*> _render_layers;

	public:
		bool init(SDL_Window* window, ECS::GameData* game_data);
		void destroy();

		void update();
		void render();

		void setLayerActive(bool is_active, int layer_offset);
		void setRenderLayerContext(ECS::RenderContext& context, int layer_offset);
		std::vector<ECS::component_id> getLayerTransforms(int layer_offset);
		
		inline SDL_Renderer* getRenderer() { if (!_render_layers.empty()) { 
			return _render_layers[0]->getRenderer(); } }
	};
}

