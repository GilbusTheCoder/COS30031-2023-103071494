#include "../hdr/Renderer.h"
#include "../../ECS/hdr/TextureLoader.h"

bool Game::Renderer::init(SDL_Window* window, ECS::GameData* game_data) {
    _textures = game_data->textures;
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
