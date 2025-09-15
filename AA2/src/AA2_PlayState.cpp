#include "AA2_PlayState.h"

#include "AA2_RefLinks.h"
#include "AA2_MenuState.h"

void AA2_PlayState::Init()
{
    SDL_SetRenderScale(AA2_RefLinks::GetRenderer(), 0.85, 0.85);
    world.Init();
}

void AA2_PlayState::Update()
{
    const bool *keys = SDL_GetKeyboardState(nullptr);

    if(keys[SDL_SCANCODE_ESCAPE])
    {
        AA2_RefLinks::GetGame()->ChangeState(new AA2_MenuState);
        return;
    }

    world.Update();
}

void AA2_PlayState::Render()
{
    world.Render();
}