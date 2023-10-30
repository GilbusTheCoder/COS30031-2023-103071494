#include "../hdr/Window.h"
#include "../hdr/Rect.h"

void pollEvents(Window* window, Rect* rect1) {
	SDL_Event* event = new SDL_Event();

	if (SDL_PollEvent(event)) {
		rect1->pollEvents(event);
		window->pollEvents(event);
	}

	delete event;
	event = nullptr;
}

int main(int argc, char* argv[]) {
	Window* window = new Window("Test window", 800, 600);
	Rect* rect = new Rect(window, 120, 120, 100, 100, 200, 0, 200, 250);

	while (window->isRunning()) {
		pollEvents(window, rect);
		rect->draw();
		window->clear(); }

	return 0;
}