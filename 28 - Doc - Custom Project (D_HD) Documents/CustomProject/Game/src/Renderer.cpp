#include "../hdr/Renderer.h"
#include "../hdr/SpriteLoader.h"

bool Game::Renderer::init(SDL_Window* window) {
    if (!window) {
        SDL_Log("No window context provided to renderer\n");
        return false; }

    _renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!_renderer) { 
        SDL_Log("Failed to instance renderer\n");
        return false; }    
    
    _textures = Game::SpriteLoader::loadTextures("Game/data/TexturePaths.txt", _renderer);
    return true; 
}

void Game::Renderer::update() { }
void Game::Renderer::render() {
    SDL_RenderClear(_renderer);
    // Render code in here
    SDL_RenderCopy(_renderer, _textures[0], nullptr, nullptr);

    SDL_RenderPresent(_renderer); }

void Game::Renderer::destroy() {
    SDL_DestroyRenderer(_renderer); }
