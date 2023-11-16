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

	if (!initRenderer(_window->getWindow())) {
		SDL_Log("Game >> Failed to init Renderer\n");
		return false; }

	if (!_event_handler->init(_window, _game_data, _renderer)) {
		SDL_Log("Game >> Failed to instance EventHandler\n");
		return false; }

	return true; }


void Game::Game::update() { _event_handler->update(); }
void Game::Game::render() { _renderer->render(); }


void Game::Game::destroy() {
	_renderer->destroy();
	_window->destroy();
	SDL_Quit();

	SDL_Log("Game >> SDL Closed.\n"); }

bool Game::Game::initRenderer(SDL_Window* window) {
	if (!_renderer->init(_window->getWindow(), _game_data)) { return false; }

	// Construct render layer context with world data
	const std::string entity_data_path = "Game/data/WorldData.txt";
	const std::string sprites_path = "Game/data/Sprite_Filepaths.txt";
	ECS::ECConstructor::initGameObjects(_game_data, _renderer->getRenderer(), entity_data_path, sprites_path);

	ECS::RenderContext r_context = {
		true,
		_game_data,
		{ECS::EntityTag::ET_HEX} };

	_renderer->setRenderLayerContext(r_context, 0);

	r_context.render_this = false;
	r_context.render_filters = { ECS::EntityTag::ET_HEX_OVERLAY };
	_renderer->setRenderLayerContext(r_context, 1);

	return true; }

