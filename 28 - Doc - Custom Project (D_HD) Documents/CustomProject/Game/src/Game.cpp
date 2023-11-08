#include "../hdr/Game.h"

Game::Game::Game() : _renderer(new Renderer()) {

}

Game::Game::~Game() {
	// Don't call Renderer.destroy() as that's called in game.destroy()
	if (_renderer) {
		delete _renderer;
		_renderer = nullptr; }
}

bool Game::Game::init(std::string title, int x, int y, int w, int h, int flags) {;
	_window->init(title, x, y, w, h, flags);
	_renderer->init(_window->getWindow());

	_event = new SDL_Event();
	if (!_event) { 
		SDL_Log("Game >> Failed to instance SDL Event\n");
		return true; }

	return true;
}

void Game::Game::update() {
	SDL_PollEvent(_event);
	_window->update(_event);
}

void Game::Game::render() { _renderer->render(); }

void Game::Game::destroy() {
	_renderer->destroy();
	_window->destroy();
	SDL_Quit();

	SDL_Log("Game >> SDL Closed.\n");
}

void Game::Game::handleEvents() {
	SDL_PollEvent(_event);
}
