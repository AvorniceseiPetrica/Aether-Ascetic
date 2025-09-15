#include "AA2_PlayState.h"

void AA2_PlayState::Init()
{
    world.Init();
}

void AA2_PlayState::Update()
{
    world.Update();
}

void AA2_PlayState::Render()
{
    world.Render();
}