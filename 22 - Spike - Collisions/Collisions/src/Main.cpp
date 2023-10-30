#include "../hdr/Window.h"
#include "../hdr/GameWorld.h"

void update(Window* window, GameWorld* world) {
	SDL_Event* event = new SDL_Event();

	if (SDL_PollEvent(event)) {
		world->update(event);
		window->update(event); }

	delete event;
	event = nullptr;
}

int main(int argc, char* argv[]) {
	Window* window = new Window("Test window", 800, 600);
	GameWorld* world = new GameWorld(window);

	while (window->isRunning()) {
		update(window, world);
		world->render();
		window->clear(); }


	if (window) { delete window; }
	if (world) { delete world; }

	window = nullptr; world = nullptr;
	return 0;
}