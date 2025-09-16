#pragma once

#include "AA_Level.h"
#include <vector>

class AA_LevelManager
{
    private:
    
        std::vector<AA_Level> levels;
        int current_level_id;
        AA_Level *current_level = nullptr;

        AA_Player player;

    public:

        AA_LevelManager(std::string levels_config_path);
        ~AA_LevelManager() = default;
        void Init();
        void Update();
        void Render();
        void ChangeLevel(long unsigned int level_id);
};