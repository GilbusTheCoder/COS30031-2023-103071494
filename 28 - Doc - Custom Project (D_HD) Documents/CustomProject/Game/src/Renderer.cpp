#include "../hdr/Renderer.h"
#include "../../ECS/hdr/TextureLoader.h"

bool Game::Renderer::init(SDL_Window* window, ECS::GameData* game_data) {
    // Init render layers
    ECS::RenderLayer* background_layer = new ECS::RenderLayer;
    ECS::RenderLayer* hex_overlayer = new ECS::RenderLayer;
    ECS::RenderContext context = { false, game_data };

    if (!background_layer->init(window, context)) {
        return false; }

    if (!hex_overlayer->init(window, context)) {
        return false; }

    _render_layers.emplace_back(background_layer);
    _render_layers.emplace_back(hex_overlayer);
    return true; }


void Game::Renderer::update() { }
void Game::Renderer::render() {
    if (!_render_layers.empty()) {
        if (_render_layers[0]->getRenderer()) {
            SDL_Renderer* render_ref = _render_layers[0]->getRenderer();
            SDL_RenderClear(render_ref);
            
            // Render code in here
            for (auto layer : _render_layers) {
                if (layer->isActive()) {
                    layer->render(); }}
            
            SDL_RenderPresent(render_ref); }
    } }


void Game::Renderer::setLayerActive(bool is_active, int layer_offset) {
    int iteration = 0;
    std::vector<ECS::RenderLayer*>::iterator layer_it = _render_layers.begin();

    for (layer_it; layer_it != _render_layers.end(); ++layer_it) {
        if (iteration == layer_offset) {
            (*layer_it)->setIsActive(is_active); }

        ++iteration; } }


void Game::Renderer::setRenderLayerContext(ECS::RenderContext& context, int layer_offset) {
    int it_count = 0;
    std::vector<ECS::RenderLayer*>::iterator  rl_it = _render_layers.begin();
    for (rl_it; rl_it != _render_layers.end(); ++rl_it) {
        if (it_count >= layer_offset) { (*rl_it)->setRenderContext(context); return; }
        ++it_count;
    } }


std::vector<ECS::component_id> Game::Renderer::getLayerTransforms(int layer_offset) {
    std::vector<ECS::component_id> layer_transform_ucids;
    
    if (!_render_layers.empty()) {
        std::vector<ECS::RenderLayer*>::iterator layer_it = _render_layers.begin();
        
        int iteration = 0;
        for (layer_it; layer_it != _render_layers.end(); ++layer_it) {
            if (iteration == layer_offset) {
                layer_transform_ucids = (*layer_it)->getLayerTransforms();
                return layer_transform_ucids; }

            ++iteration; }
    }

    return layer_transform_ucids; }


void Game::Renderer::destroy() {
    for (auto layer : _render_layers) {
        layer->destroy(); } }