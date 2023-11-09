#include "../hdr/TransformLoader.h"

ECS::Transform ECS::TransformLoader::loadTransformComponent(
	std::string comp_id, std::string args) {
	Transform transform = {
		comp_id,
		C_TRANSFORM,

		determineBounds(args),
		calculateOrigin(determineBounds(args)),
	};

	return transform;
}

SDL_Point ECS::TransformLoader::calculateOrigin(SDL_Rect bounds) {
	SDL_Point point = {
		bounds.x + 0.5 * bounds.w,
		bounds.y + 0.5 * bounds.h,
	};

	return point;
}

SDL_Rect ECS::TransformLoader::determineBounds(std::string unfmt_bounds) {
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
