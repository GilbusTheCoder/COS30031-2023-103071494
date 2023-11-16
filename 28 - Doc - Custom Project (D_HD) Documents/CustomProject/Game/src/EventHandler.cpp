#include "../hdr/EventHandler.h"
#include <SDL_log.h>

bool ECS::EventHandler::init(Game::Window* window_ref, GameData* game_data_ref, 
    Game::Renderer* renderer_ref) {
    _window = window_ref;
    if (!_window) {
        SDL_Log("EventHandler >> No window instance given to EventHandler\n");
        return false; }

    _event = new SDL_Event();
    if (!_event) {
        SDL_Log("EventHandler >> Failed to instance SDL Event\n");
        return false; }

    InteractionContext init_context = {
        game_data_ref,
        renderer_ref };

    if (!_is->init(init_context)) {
        SDL_Log("EventHandler >> failed to initialize Interaction System\n");
        return false; }

    return true; }

void ECS::EventHandler::update() {
    SDL_PollEvent(_event);
    dispatchEvents(); }


void ECS::EventHandler::destroy() {
    delete _event;
    _event = nullptr; }


void ECS::EventHandler::dispatchEvents() {
    // First we check for meta events (window clicks and interactions)
    // then determine which systems need to be called on interaction
    switch (_event->type) {
    case SDL_QUIT:
        _window->setIsRunning(false); 
        break;
    case SDL_MOUSEMOTION: {   
        SDL_GetMouseState(&_is_context.m_x, &_is_context.m_y);
        _is->update(_is_context);
        break; 
    case SDL_MOUSEBUTTONUP: {
        _is_context.click_event = _event;
        SDL_GetMouseState(&_is_context.m_x, &_is_context.m_y);
        break; } }
    }
}

