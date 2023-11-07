#include "../hdr/Game.h"

Game::Game::Game() : _renderer(new Renderer()) {

}

Game::Game::~Game() {
	// Don't call Renderer.destroy() as that's called in game.destroy()
	if (_renderer) {
		delete _renderer;
		_renderer = nullptr; }
}

bool Game::Game::init(std::string title, int x, int y, int w, int h, bool fullscreen) {
	bool is_success = false;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) > 0) {
		SDL_Log("Failed to init SDL Video or Events subsystems\n");
		return is_success; }

	int w_flags = 0;
	fullscreen ? w_flags = SDL_WINDOW_FULLSCREEN : w_flags = 0;
	_window = SDL_CreateWindow(title.c_str(), x, y, w, h, w_flags);
	if (!_window) { SDL_Log("Failed to instance window\n"); return is_success; }

	_renderer->init(_window);

	_event = new SDL_Event();
	if (_event) { is_success = true; }

	_is_running = is_success;
	return is_success;
}

void Game::Game::update() { handleEvents(); }

void Game::Game::render() { _renderer->render(); }

void Game::Game::destroy() {
	_renderer->destroy();
	SDL_DestroyWindow(_window);
	SDL_Quit();

	SDL_Log("SDL Closed.\n");
}

void Game::Game::handleEvents() {
	SDL_PollEvent(_event);

	switch (_event->type) {
	case SDL_QUIT:
		_is_running = false;
		break;
	default:
		break; }
}
