#include <SDL.h>
#include <string>

#pragma once
namespace ECS {
	typedef std::string component_id;
	typedef std::string label_contents, label_font;

	enum ComponentType {
		C_TRANSFORM,
		C_TEXTURE,
		C_UILABEL,
		C_INTERACTABLE,
		C_MOVABLE, 
		C_TAG,
		C_INVALID, };

	enum EntityTag {
		ET_HEX,
		ET_ARMY,
		ET_BUILDING,
		ET_HEX_OVERLAY,
		ET_NEW_TAG,
		ET_INVALID,	};

	struct Component {
		component_id id = "ZZZZzzzz";
		ComponentType type = ComponentType::C_INVALID; };


	struct Transform : public Component {
		SDL_Rect bounds; 
		SDL_Point origin; };

	
	struct Texture : public Component {
		SDL_Texture* texture = nullptr;
		SDL_Rect bounds = { 0,0,0,0 };
		bool render_this = false; };


	struct UILabel : public Component {
		SDL_Texture* label = nullptr;
		SDL_Rect bounds = { 0,0,0,0 };
		SDL_Color colour = { 0,0,0,0 };

		label_contents text = "";
		label_font font = "arial"; 	};


	struct Interactable : public Component { 
		bool is_interactable = false; };


	struct Movable : public Component {
		bool can_move = false;
		int radius = 0;	};


	struct Tag : public Component {	EntityTag tag = ET_INVALID; };
}

