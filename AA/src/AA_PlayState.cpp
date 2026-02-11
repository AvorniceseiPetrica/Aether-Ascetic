#include "AA_PlayState.h"

#include "AA_RefLinks.h"
#include "AA_MenuState.h"
#include "AA_GameOverState.h"

void AA_PlayState::Init()
{
    SDL_SetRenderScale(AA_RefLinks::GetRenderer(), 0.85, 0.85);
    world.Init();

    SDL_Log("Playstate initialized...\n");
}

void AA_PlayState::HandleEvents()
{
    SDL_Event e;

    while(SDL_PollEvent(&e))
    {
        if(e.type == SDL_EVENT_QUIT)
        {
            exit(0);
            return;
        }
    }
}

void AA_PlayState::Update()
{
    const bool *keys = SDL_GetKeyboardState(nullptr);

    if(AA_RefLinks::GetPlayer()->GetHealth() <= 0)
        AA_RefLinks::GetGame()->ChangeState(new AA_GameOverState);

    world.Update();
}

void AA_PlayState::Render()
{
    world.Render();
}