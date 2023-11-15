#include "../hdr/Game.h"
#include "../../ECS/hdr/ECConstructor.h"

Game::Game::Game() : _renderer(new Renderer()) { }


Game::Game::~Game() {
	// Don't call Renderer.destroy() as that's called in game.destroy()
	if (_renderer) {
		delete _renderer;
		_renderer = nullptr; } }


bool Game::Game::init(std::string title, int x, int y, int w, int h, int flags) {
	_game_data = new ECS::GameData();

	if (!_window->init(title, x, y, w, h, flags)) {
		SDL_Log("Game >> Failed to init Window\n");
		return false; }

	if (!_renderer->init(_window->getWindow(), _game_data)) {
		SDL_Log("Game >> Failed to init Renderer\n");
		return false; }

	const std::string entity_data_path = "Game/data/WorldData.txt";
	const std::string sprites_path = "Game/data/Sprite_Filepaths.txt";
	ECS::ECConstructor::initGameObjects(_game_data, _renderer->getRenderer(), entity_data_path, sprites_path);
	_renderer->setRenderLayerContext(_game_data, 0);

	_event = new SDL_Event();
	if (!_event) { 
		SDL_Log("Game >> Failed to instance SDL Event\n");
		return true; }

	return true; }


void Game::Game::update() {
	SDL_PollEvent(_event);
	_window->update(_event); }


void Game::Game::render() { _renderer->render(); }


void Game::Game::destroy() {
	_renderer->destroy();
	_window->destroy();
	SDL_Quit();

	SDL_Log("Game >> SDL Closed.\n"); }

