#include "AA_PlayState.h"

#include "AA_RefLinks.h"
#include "AA_MenuState.h"

void AA_PlayState::Init()
{
    SDL_SetRenderScale(AA_RefLinks::GetRenderer(), 0.85, 0.85);
    world.Init();

    SDL_Log("Playstate initialized...\n");
}

void AA_PlayState::Update()
{
    const bool *keys = SDL_GetKeyboardState(nullptr);

    if(keys[SDL_SCANCODE_ESCAPE])
    {
        AA_RefLinks::GetGame()->ChangeState(new AA_MenuState);
        return;
    }

    world.Update();
}

void AA_PlayState::Render()
{
    world.Render();
}