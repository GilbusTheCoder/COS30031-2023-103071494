#include "../hdr/Renderer.h"
#include "../../ECS/hdr/TextureLoader.h"

bool Game::Renderer::init(SDL_Window* window, ECS::GameData* game_data) {
    // Init render layers
    ECS::RenderLayer* background_layer = new ECS::RenderLayer;
    ECS::RenderContext context = { game_data };
    
    if (!background_layer->init(window, context)) {
        return false; }

    _render_layers.emplace_back(background_layer);
    return true; }


void Game::Renderer::update() { }


void Game::Renderer::render() {
    bool has_renderer = false;
    if (!_render_layers.empty()) {
        if (_render_layers[0]->getRenderer()) {
            SDL_Renderer* render_ref = _render_layers[0]->getRenderer();
            SDL_RenderClear(render_ref);
            
            // Render code in here
            for (auto layer : _render_layers) {
                layer->render(); }
            
            SDL_RenderPresent(render_ref); }
    } }

void Game::Renderer::setRenderLayerContext(ECS::GameData* game_data, int layer_offset) {
     ECS::RenderContext context = { 
        game_data,
        { ECS::EntityTag::ET_HEX } 
    };

    int it_count = 0;
    std::vector<ECS::RenderLayer*>::iterator  rl_it = _render_layers.begin();
    for (rl_it; rl_it != _render_layers.end(); ++rl_it) {
        if (it_count >= layer_offset) { (*rl_it)->setRenderContext(context); }
        ++it_count;
    }
}


void Game::Renderer::destroy() {
    for (auto layer : _render_layers) {
        layer->destroy(); } }