#include <vector>
#include "../../Game/hdr/GameData.h"
#include "../../Game/hdr/Renderer.h"

#pragma once
namespace ECS {
	/*	This system is called whenever the player interacts with an entity via 
	*	mouse input. This basically boils down to setting active render layers
	*	making sure that the correct entity is selected (the top layer entity)
	*	when input collision occurs											*/
	
	// ho = hex overlay
	typedef int bg_layer_offset, ho_layer_offset;
	
	enum InteractionState {
		IS_DEFAULT,
		IS_HEX_SELECTED,
		IS_INVALID	};
	
	struct InteractionContext {
		GameData* game_data_ref = nullptr;
		Game::Renderer* renderer_ref = nullptr;

		Sint32 m_x=0, m_y=0;
		bool mouse_clicked = false;
		int lmb_or_rmb = 0;	// 1 for LMB, 2 for RMB
	};
	
	class InteractionSystem {
	private:
		GameData* _game_data_ref = nullptr;
		Game::Renderer* _renderer_ref = nullptr;
		bg_layer_offset _bg_offset = 0;
		ho_layer_offset _hex_overlay_offset = 1;
		
		std::vector<component_id> _bg_hex_ucids;
		component_id _hex_highlight_ucid;

	public:
		bool init(InteractionContext& context);
		void update(InteractionContext& context);

	private:
		void handleMouseClick(InteractionContext& context);
		void handleMouseHexHover(InteractionContext& context);
		bool transformPointCollision(Transform& transform, Sint32 mouse_x, Sint32 mouse_y); };
}