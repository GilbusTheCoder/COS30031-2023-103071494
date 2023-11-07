#include "../hdr/Game.h"

const int FPS = 60;
const int max_frame_time = 1000 / FPS;

Uint32 frame_start;
int frame_time;

int main(int argc, char** argv) {
	Game::Game* game = new Game::Game();
	game->init("Custom Project - Thomas Horsley 103071494",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600, false);

	while (game->isRunning()) {
		frame_start = SDL_GetTicks();

		game->update();
		game->render();	}


	// FPS Cap stuff
	frame_time = SDL_GetTicks() - frame_start;
	if (max_frame_time > frame_time) {
		SDL_Delay(max_frame_time - frame_time);	}

	game->destroy();
	return 0;
}
