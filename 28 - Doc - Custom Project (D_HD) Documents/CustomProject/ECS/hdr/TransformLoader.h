#include "CompLoader.h"
#pragma once

/*	Expects args in the form <"x,y,w,h">. Only 1 arg expected		*/
namespace ECS {
	class TransformLoader : public CompLoader {
	public:
		static Transform loadTransformComponent(std::string comp_id,
			std::string args);

	private:
		static SDL_Point calculateOrigin(SDL_Rect bounds);
		static SDL_Rect determineBounds(std::string unfmt_bounds);
	};
}
