#include "AA_LevelManager.h"

#include <fstream>
#include "AA_RefLinks.h"

AA_LevelManager::AA_LevelManager(std::string levels_config_path) : player(0, 0)
{
    std::fstream f;

    f.open(levels_config_path);

    if(!f.is_open())
        SDL_Log("\n\tAA_LevelManager::AA_LevelManager()\t<< Could not open config file >>\n\n");
    else
        while(!f.eof())
        {
            std::string map_path;
            std::string props_config_path;
            std::string background_path, midground1_path, midground2_path;
            int player_spawn_x, player_spawn_y;

            f>>map_path>>props_config_path>>player_spawn_x>>player_spawn_y>>background_path>>midground1_path>>midground2_path;

            levels.push_back(AA_Level(map_path, props_config_path, {.x = player_spawn_x, .y = player_spawn_y}, background_path, midground1_path, midground2_path));
        }
}

void AA_LevelManager::Init()
{
    current_level_id = 0;
    ChangeLevel(current_level_id);
    
    player.Init();
    
    AA_RefLinks::SetPlayer(&player);
    AA_RefLinks::GetCamera()->SetTarget(player.GetRect());
}

void AA_LevelManager::Update()
{
    if(AA_RefLinks::GetPlayer()->GetRect()->x > MAP_WIDTH - TILE_WIDTH)
    {
        ChangeLevel(++current_level_id);
        return;
    }

    current_level->Update();
    player.Update();
}

void AA_LevelManager::Render()
{
    current_level->Render();
    player.Render();
}

void AA_LevelManager::ChangeLevel(long unsigned int level_id)
{
    if(level_id >= levels.size())
    {
        SDL_Log("\n\tAA_LevelManager::ChangeLevel()\t<< Invalid level id | level_id = %ld >>\n\n", level_id);
        return;
    }

    current_level = &levels[level_id];
    current_level->Init();
    player.ChangePosition(current_level->GetPlayerSpawn().x, current_level->GetPlayerSpawn().y);
}