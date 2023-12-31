#include <string>
#include <SDL.h>

#pragma once
namespace Game {
	class Window {
	private:
		SDL_Window* _window = nullptr;

		const char* _title = "";
		int _x=0, _y=0, _w=0, _h=0, _flags=0;
		bool _is_running = false;

	public:
		bool init(std::string title, int xpos, int ypos, int width, int height, int flags);
		void destroy();

		inline SDL_Window* getWindow() { return _window; }
		inline const std::pair<int, int> getDimensions() { return { _w, _h }; }
		inline const std::pair<int, int> getPos() { return { _x, _y }; }

		inline void setIsRunning(bool is_running) { _is_running = is_running; }
		inline const bool isRunning() { return _is_running; }
	};
}

