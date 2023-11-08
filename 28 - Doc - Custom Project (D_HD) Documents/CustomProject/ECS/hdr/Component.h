#include <SDL.h>
#include <string>

#pragma once
namespace ECS {
	typedef std::string component_id;

	enum ComponentType {
		C_TRANSFORM,
		C_ORIGIN,
		C_TEXTURE,
		C_UILABEL,
		C_INTERACTABLE,
		C_MOVABLE, 
		C_INVALID, };

	struct Component {
		component_id id;
		ComponentType type;
	};

	struct Transform : public Component {
		SDL_Rect bounds; };

	struct Origin : public Component { 
		SDL_Point origin; };
	
	struct Texture : public Component {
		bool render_this = false;
		SDL_Texture* texture = nullptr;
		SDL_Rect bounds;
	};
}

