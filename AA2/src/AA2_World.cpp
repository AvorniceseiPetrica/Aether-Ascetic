#include "AA2_World.h"

#include "AA2_RefLinks.h"

AA2_World::~AA2_World()
{
    if(level_manager != nullptr)
        delete level_manager;
}

void AA2_World::Init()
{
    AA2_RefLinks::SetCamera(&camera);
    level_manager = new AA2_LevelManager("configs/levels_config.txt");
    level_manager->Init();
    camera.SetTarget(AA2_RefLinks::GetPlayer()->GetRect());
}

void AA2_World::Update()
{
    level_manager->Update();
    camera.Update();
}

void AA2_World::Render()
{
    level_manager->Render();
}