#pragma once
#include <string>
#include <SDL.h>

class Window {
private:
	bool _is_running = true;
	SDL_Window* _window = nullptr;
	SDL_Renderer* _renderer = nullptr;
	
	std::string _title;
	int _width, _height;

public:
	Window(const std::string& title, int width, int height);
	~Window();

	inline bool isRunning() const { return _is_running; };
	inline SDL_Renderer* getRenderer() const { return _renderer; }

	void pollEvents(SDL_Event* event);
	void clear() const;

private:
	bool init();
};
