#include "AA2_LevelManager.h"

#include <fstream>

AA2_LevelManager::AA2_LevelManager(std::string levels_config_path)
{
    std::fstream f;

    f.open(levels_config_path);

    if(!f.is_open())
        SDL_Log("Could not open levels_config_path");
    else
    {
        std::string map_path;
        int player_spawn_x, player_spawn_y;

        f>>map_path>>player_spawn_x>>player_spawn_y;

        levels.push_back(AA2_Level(map_path, {.x = player_spawn_x, .y = player_spawn_y}));
    }
}

void AA2_LevelManager::Init()
{
    current_level_id = 0;
    ChangeLevel(current_level_id);
}

void AA2_LevelManager::Update()
{
    current_level->Update();
}

void AA2_LevelManager::Render()
{
    current_level->Render();
}

void AA2_LevelManager::ChangeLevel(int level_id)
{
    current_level = &levels[level_id];
    level_id++;
    current_level->Init();
}