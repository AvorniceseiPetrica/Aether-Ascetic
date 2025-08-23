#pragma once

#include "AA2_Map.h"
#include "AA2_Player.h"
#include "AA2_PropManager.h"

class AA2_Level
{
    private:

        AA2_Map map;
        std::string map_path;

        AA2_Player player;

        SDL_Texture *background = nullptr;
        std::string background_path;

        SDL_Texture *midground = nullptr;
        std::string midground_path;

        float background_parallax = 0.3;
        float midground_parallax = 0.8;

        AA2_PropManager props;
        std::string props_config_path;

    public:

        AA2_Level(std::string p_map_path, std::string p_props_config_path, SDL_Point p_player_spawn);
        ~AA2_Level();
        void Init();
        void Update();
        void Render();
        void RenderBackground();
        void RenderMidground();
};