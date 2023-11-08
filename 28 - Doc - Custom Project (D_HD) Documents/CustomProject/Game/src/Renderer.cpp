#include "../hdr/Renderer.h"
#include "../../ECS/hdr/TextureLoader.h"

bool Game::Renderer::init(SDL_Window* window) {
    if (!window) {
        SDL_Log("Renderer >> No window context provided to renderer\n");
        return false; }

    _renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!_renderer) { 
        SDL_Log("Renderer >> Failed to instance renderer\n");
        return false; }    
    
    _textures = ECS::TextureLoader::loadTextures(_renderer);
    return true; 
}

void Game::Renderer::update() { }
void Game::Renderer::render() {
    SDL_RenderClear(_renderer);
    // Render code in here
    for (auto texture : _textures) {
        ECS::Texture current_texture = texture.second;
        SDL_RenderCopy(_renderer, current_texture.texture, nullptr, &current_texture.bounds);  }

    SDL_RenderPresent(_renderer); }

void Game::Renderer::destroy() {
    SDL_DestroyRenderer(_renderer);
    _renderer = nullptr;
}
