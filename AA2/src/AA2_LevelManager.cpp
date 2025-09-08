#include "AA2_LevelManager.h"

#include <fstream>
#include "AA2_RefLinks.h"

AA2_LevelManager::AA2_LevelManager(std::string levels_config_path) : player(0, 0)
{
    std::fstream f;

    f.open(levels_config_path);

    if(!f.is_open())
        SDL_Log("Could not open levels_config_path");
    else
        while(!f.eof())
        {
            std::string map_path;
            std::string props_config_path;
            int player_spawn_x, player_spawn_y;

            f>>map_path>>props_config_path>>player_spawn_x>>player_spawn_y;

            levels.push_back(AA2_Level(map_path, props_config_path, {.x = player_spawn_x, .y = player_spawn_y}));
        }
}

void AA2_LevelManager::Init()
{
    current_level_id = 0;
    ChangeLevel(current_level_id);
    
    player.Init();

    for(auto &level : levels)
        level.Init();
    
    AA2_RefLinks::SetPlayer(&player);
    AA2_RefLinks::GetCamera()->SetTarget(player.GetRect());
}

void AA2_LevelManager::Update()
{
    if(AA2_RefLinks::GetPlayer()->GetRect()->x > MAP_WIDTH - TILE_WIDTH * 3)
    {
        ChangeLevel(++current_level_id);
        return;
    }

    current_level->Update();
    player.Update();
}

void AA2_LevelManager::Render()
{
    current_level->Render();
    player.Render();
}

void AA2_LevelManager::ChangeLevel(long unsigned int level_id)
{
    if(level_id >= levels.size())
    {
        SDL_Log("Invalid level id\n");
        return;
    }

    current_level = &levels[level_id];
    //current_level->Init();
    player.ChangePosition(current_level->GetPlayerSpawn().x, current_level->GetPlayerSpawn().y);
}