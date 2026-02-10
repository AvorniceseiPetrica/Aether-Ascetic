#include "AA_World.h"

#include "AA_RefLinks.h"
#include "AA_TextureLoader.h"

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

    SDL_FRect *player_rect = AA_RefLinks::GetPlayer()->GetData();

    camera.SetTarget(player_rect);

    hearts[0] = AA_TextureLoader::LoadTexture("assets/sprites/ui/hearts1.png");
    hearts[1] = AA_TextureLoader::LoadTexture("assets/sprites/ui/hearts2.png");
    hearts[2] = AA_TextureLoader::LoadTexture("assets/sprites/ui/hearts3.png");

    SDL_Log("World initialized...\n");
}

void AA_World::Update()
{
    level_manager->Update();
    camera.Update();
}

void AA_World::Render()
{
    SDL_FRect dst = {
        .x = 0,
        .y = 0,
        .w = 64 * AA_RefLinks::GetPlayer()->GetHealth(),
        .h = 64
    };

    level_manager->Render();
    SDL_RenderTexture(AA_RefLinks::GetRenderer(), hearts[AA_RefLinks::GetPlayer()->GetHealth() - 1], nullptr, &dst);
}