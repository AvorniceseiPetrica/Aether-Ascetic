#include "AA2_MenuState.h"

#include "AA2_TextureLoader.h"
#include "AA2_RefLinks.h"

void AA2_MenuState::Init()
{
    background = AA2_TextureLoader::LoadTexture("assets/menu/background.png");
    start_game_button = AA2_TextureLoader::LoadTexture("assets/menu/start_game.png");
    quit_game_button = AA2_TextureLoader::LoadTexture("assets/menu/quit_game.png");
}

void AA2_MenuState::Update()
{

}

void AA2_MenuState::Render()
{
    SDL_RenderTexture(AA2_RefLinks::GetRenderer(), background, nullptr, &background_rect);
    SDL_RenderTexture(AA2_RefLinks::GetRenderer(), start_game_button, nullptr, &start_game_rect);
    SDL_RenderTexture(AA2_RefLinks::GetRenderer(), quit_game_button, nullptr, &quit_game_rect);
}