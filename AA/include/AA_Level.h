#pragma once

#include "AA_Map.h"
#include "AA_Player.h"
#include "AA_PropManager.h"

#include "AA_Ghoul.h"
#include <vector>

class AA_Level
{
    private:

        AA_Map map;
        std::string map_path;

        std::vector <SDL_Texture*> layers;
        std::string layers_config;
        std::vector <float> layers_parallaxes;

        AA_PropManager props;
        std::string props_config_path;

        SDL_Point player_spawn;

        AA_Ghoul *ghoul;

    public:

        AA_Level(std::string p_map_path, std::string p_props_config_path, SDL_Point p_player_spawn, std::string p_layers_config);
        ~AA_Level();
        void Init();
        void Update();
        void Render();
        void RenderLayers();
        SDL_Point GetPlayerSpawn();
};