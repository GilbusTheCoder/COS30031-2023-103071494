#include "../hdr/InteractionSystem.h"

bool ECS::InteractionSystem::init(InteractionContext& context) {
	_game_data_ref = context.game_data_ref;
	if (!_game_data_ref) {
		SDL_Log("InteractionSystem >> No gamedata instance provided\n");
		return false; }

	_renderer_ref = context.renderer_ref;
	if (!_renderer_ref) {
		SDL_Log("InteractionSystem >> No renderer instance provided\n");
		return false; }

	_bg_hex_ucids = context.renderer_ref->getLayerTransforms(0);
	if (_bg_hex_ucids.empty()) {
		SDL_Log("InteractionSystem >> No background hex id's were initialized\n");
		return false; }

	_hex_highlight_ucid = _renderer_ref->getLayerTransforms(1)[0];
	return true; }


void ECS::InteractionSystem::update(InteractionContext& context) {
	handleMouseHexHover(context); }


void ECS::InteractionSystem::handleMouseClick(InteractionContext& context) {
		
}


void ECS::InteractionSystem::handleMouseHexHover(InteractionContext& context) {
	for (component_id trans_id : _bg_hex_ucids) {
		Sint32 x = context.m_x, y = context.m_y;

		if (transformPointCollision(_game_data_ref->transforms[trans_id], x, y)) {
			_renderer_ref->setLayerActive(true, _hex_overlay_offset);

			_game_data_ref->transforms[_hex_highlight_ucid] = 
				_game_data_ref->transforms[trans_id];
			_game_data_ref->textures[_hex_highlight_ucid].bounds = 
				_game_data_ref->transforms[trans_id].bounds;

			SDL_Log("x: %i | y: %i | id: %s", context.m_x, context.m_y, trans_id.c_str()); 
			break;
		} else { _renderer_ref->setLayerActive(false, _hex_overlay_offset); }
	} }


/*	The issue here is that we're using square colliding boxes for
*	transforms and storing hexagons in them. This causes overlap on
*	the corners of transforms. To fix this im going to determine which
*	hexagons center the input was closest to (origin stored in the
*	transform) and that should work...							*/
bool ECS::InteractionSystem::transformPointCollision(Transform& transform,
	Sint32 mouse_x, Sint32 mouse_y) {
	if (!(mouse_x > transform.bounds.x) || !(mouse_x < (transform.bounds.x + transform.bounds.w))) {
		return false; }

	if (!(mouse_y > (transform.bounds.y)) || !(mouse_y < (transform.bounds.y + transform.bounds.h))) {
		return false; }
	
	return true; }