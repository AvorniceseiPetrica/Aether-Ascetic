#include "AA2_MenuState.h"

#include "AA2_TextureLoader.h"
#include "AA2_RefLinks.h"
#include "AA2_PlayState.h"

void AA2_MenuState::Init()
{
    background = AA2_TextureLoader::LoadTexture("assets/menu/background.png");
    start_game_button_unpressed = AA2_TextureLoader::LoadTexture("assets/menu/start_game.png");
    start_game_button_pressed = AA2_TextureLoader::LoadTexture("assets/menu/start_game_pressed.png");
    quit_game_button_unpressed = AA2_TextureLoader::LoadTexture("assets/menu/quit_game.png");
    quit_game_button_pressed = AA2_TextureLoader::LoadTexture("assets/menu/quit_game_pressed.png");

    start_game_pressed = false;
    quit_game_pressed = false;
    
    SDL_SetRenderScale(AA2_RefLinks::GetRenderer(), 1, 1);
}

void AA2_MenuState::Update()
{
    const bool *keys = SDL_GetKeyboardState(nullptr);

    if(keys[SDL_SCANCODE_1] && !keys[SDL_SCANCODE_2])
    {
        start_game_pressed = true;
        quit_game_pressed = false;
    }

    if(keys[SDL_SCANCODE_2] && !keys[SDL_SCANCODE_1])
    {
        quit_game_pressed = true;
        start_game_pressed = false;
    }
    
    if(keys[SDL_SCANCODE_RETURN])
    {
        if(start_game_pressed)
            AA2_RefLinks::GetGame()->ChangeState(new AA2_PlayState);
        if(quit_game_pressed)
            exit(0);
    }
}

void AA2_MenuState::Render()
{
    SDL_RenderTexture(AA2_RefLinks::GetRenderer(), background, nullptr, &background_rect);
    
    if(start_game_pressed)
        SDL_RenderTexture(AA2_RefLinks::GetRenderer(), start_game_button_pressed, nullptr, &start_game_rect);
    else
        SDL_RenderTexture(AA2_RefLinks::GetRenderer(), start_game_button_unpressed, nullptr, &start_game_rect);
    
    if(quit_game_pressed)
        SDL_RenderTexture(AA2_RefLinks::GetRenderer(), quit_game_button_pressed, nullptr, &quit_game_rect);
    else
        SDL_RenderTexture(AA2_RefLinks::GetRenderer(), quit_game_button_unpressed, nullptr, &quit_game_rect);
}