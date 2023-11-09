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
		component_id id = "ZZZZzzzz";
		ComponentType type = ComponentType::C_INVALID;
	};

	struct Transform : public Component {
		SDL_Rect bounds; };

	struct Origin : public Component { 
		SDL_Point origin; };
	
	struct Texture : public Component {
		SDL_Texture* texture = nullptr;
		SDL_Rect bounds = {0,0,0,0};
		bool render_this = false;
	};

	struct UILabel : public Component { };
	struct Interactable : public Component { };
	struct Movable : public Component { };
}

