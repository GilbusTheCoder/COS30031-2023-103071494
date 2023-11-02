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
		inline std::pair<int, int> getPos() { return { _x, _y }; }
		inline ShapeType getType() { return _type; }
		inline ColourRGBA getColour() { return _colour; }

		virtual void setPos(std::pair<int, int> pos) = 0;
		inline void setType(ShapeType type) { _type = type; }
		inline void setColour(ColourRGBA colour) { _colour = colour; }

		virtual void render() = 0;

	protected:
		virtual void findBounds() = 0;
	};
}

