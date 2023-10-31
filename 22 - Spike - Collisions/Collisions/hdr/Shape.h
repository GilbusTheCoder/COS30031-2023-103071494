#pragma once
#include <utility>
#include <SDL.h>

namespace Shape {
	enum class ShapeType {
		INVALID,
		RECT,
		CIRCLE,
		LINE,
	};

	struct ColourRGBA { int r=255, g=255, b=255, a=255; };
	 
	class Shape {
	protected:
		SDL_Renderer* _renderer = nullptr;

		int _x=0, _y=0;
		ShapeType _type = ShapeType::INVALID;
		ColourRGBA _colour;
		SDL_Rect* _bounds = nullptr;

	public:
		inline ShapeType getType() { return _type; }
		inline ColourRGBA getColour() { return _colour; }
		inline std::pair<int, int> getPos() { return { _x, _y }; }

		inline void setType(ShapeType type) { _type = type; }
		inline void setColour(ColourRGBA colour) { _colour = colour; }
		inline virtual void setPos(std::pair<int, int> pos) { auto [_x, _y] = pos; }

		virtual void render() = 0;

	protected:
		virtual void findBounds() = 0;
	};
}

