#pragma once

#include "AA_Map.h"
#include "AA_Player.h"
#include "AA_PropManager.h"

#include "AA_Ghoul.h"

class AA_Level
{
    private:

        AA_Map map;
        std::string map_path;

        SDL_Texture *background = nullptr;
        std::string background_path;

        SDL_Texture *midground1 = nullptr;
        std::string midground1_path;

        SDL_Texture *midground2 = nullptr;
        std::string midground2_path;

        float background_parallax = 0.2;
        float midground1_parallax = 0.35;
        float midground2_parallax = 0.45;

        AA_PropManager props;
        std::string props_config_path;

        SDL_Point player_spawn;

        AA_Ghoul *ghoul;

    public:

        AA_Level(std::string p_map_path, std::string p_props_config_path, SDL_Point p_player_spawn);
        ~AA_Level();
        void Init();
        void Update();
        void Render();
        void RenderBackground();
        void RenderMidground1();
        void RenderMidground2();
        SDL_Point GetPlayerSpawn();
};