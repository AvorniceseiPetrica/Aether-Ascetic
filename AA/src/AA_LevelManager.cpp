#include "AA_LevelManager.h"

#include <fstream>
#include "AA_RefLinks.h"
#include "AA_WinState.h"

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
            std::string layers_config_path;
            std::string enemies_config_path;
            int player_spawn_x, player_spawn_y;

            f>>map_path>>player_spawn_x>>player_spawn_y>>layers_config_path>>enemies_config_path;

            levels.push_back(AA_Level(map_path, {.x = player_spawn_x, .y = player_spawn_y}, layers_config_path, enemies_config_path));
        }
}

void AA_LevelManager::Init()
{
    current_level_id = 0;
    player.Init();
    
    ChangeLevel(current_level_id);
    
    AA_RefLinks::SetPlayer(&player);

    SDL_FRect *player_hitbox = player.GetBodyHitbox();

    SDL_Log("Level manager initialized...\n");
}

void AA_LevelManager::Update()
{
    if(AA_RefLinks::GetPlayer()->GetData()->x > MAP_WIDTH - TILE_WIDTH)
    {
        if(current_level_id == 3)
        {
            AA_RefLinks::GetGame()->ChangeState(new AA_WinState);
            return;
        }

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
        
        current_level_id = levels.size() - 1;
        return;
    }

    current_level = &levels[level_id];
    
    current_level->Init();

    player.ChangePosition(current_level->GetPlayerSpawn().x, current_level->GetPlayerSpawn().y);

    //SDL_Log("clid = %d, a = %lu, x = %f", current_level_id, levels.size() - 1, AA_RefLinks::GetPlayer()->GetData()->x);

    if(current_level_id == levels.size() - 1 && AA_RefLinks::GetPlayer()->GetData()->x > MAP_WIDTH - 3 * TILE_WIDTH)
        AA_RefLinks::GetGame()->ChangeState(new AA_WinState);

    //AA_RefLinks::SetCurrentLevelId(level_id);

    player.ChangeState(PLAYER_FALL);
}