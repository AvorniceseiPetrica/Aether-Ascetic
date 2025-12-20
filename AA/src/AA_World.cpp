#include "AA_World.h"

#include "AA_RefLinks.h"

AA_World::~AA_World()
{
    if(level_manager != nullptr)
        delete level_manager;
}

void AA_World::Init()
{
    AA_RefLinks::SetCamera(&camera);
    level_manager = new AA_LevelManager("configs/levels_config.txt");
    level_manager->Init();

    SDL_FRect *player_hitbox = AA_RefLinks::GetPlayer()->GetBodyHitbox();

    camera.SetTarget(player_hitbox);

    SDL_Log("World initialized...\n");
}

void AA_World::Update()
{
    level_manager->Update();
    camera.Update();
}

void AA_World::Render()
{
    level_manager->Render();
}