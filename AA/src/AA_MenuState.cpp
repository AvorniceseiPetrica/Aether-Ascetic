#include "AA_MenuState.h"

#include "AA_TextureLoader.h"
#include "AA_RefLinks.h"
#include "AA_PlayState.h"

void AA_MenuState::Init()
{
    background = AA_TextureLoader::LoadTexture("assets/menu/background.png");
    start_game_button_unpressed = AA_TextureLoader::LoadTexture("assets/menu/start_game.png");
    start_game_button_pressed = AA_TextureLoader::LoadTexture("assets/menu/start_game_pressed.png");
    quit_game_button_unpressed = AA_TextureLoader::LoadTexture("assets/menu/quit_game.png");
    quit_game_button_pressed = AA_TextureLoader::LoadTexture("assets/menu/quit_game_pressed.png");

    start_game_pressed = false;
    quit_game_pressed = false;
    
    SDL_SetRenderScale(AA_RefLinks::GetRenderer(), 1, 1);
}

void AA_MenuState::Update()
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
            AA_RefLinks::GetGame()->ChangeState(new AA_PlayState);
        if(quit_game_pressed)
            exit(0);
    }
}

void AA_MenuState::Render()
{
    SDL_RenderTexture(AA_RefLinks::GetRenderer(), background, nullptr, &background_rect);
    
    if(start_game_pressed)
        SDL_RenderTexture(AA_RefLinks::GetRenderer(), start_game_button_pressed, nullptr, &start_game_rect);
    else
        SDL_RenderTexture(AA_RefLinks::GetRenderer(), start_game_button_unpressed, nullptr, &start_game_rect);
    
    if(quit_game_pressed)
        SDL_RenderTexture(AA_RefLinks::GetRenderer(), quit_game_button_pressed, nullptr, &quit_game_rect);
    else
        SDL_RenderTexture(AA_RefLinks::GetRenderer(), quit_game_button_unpressed, nullptr, &quit_game_rect);
}