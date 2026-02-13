#pragma once

#include <SDL3/SDL.h>
#include "AA_Camera.h"
#include "AA_Player.h"
#include "AA_Map.h"
#include "AA_Game.h"

class AA_RefLinks
{
    private:

        static SDL_Window *window;
        static SDL_Renderer *renderer;
        static AA_Camera *camera;
        static AA_Player *player;
        static AA_Map *map;
        static AA_Game *game;
        static int current_level_id;

    public:

        static void SetWindow(SDL_Window *p_window);
        static SDL_Window* GetWindow();
        static void SetRenderer(SDL_Renderer *p_renderer);
        static SDL_Renderer* GetRenderer();
        static void SetCamera(AA_Camera *p_camera);
        static AA_Camera* GetCamera();
        static void SetPlayer(AA_Player *p_player);
        static AA_Player* GetPlayer();
        static void SetMap(AA_Map *p_map);
        static AA_Map* GetMap();
        static void SetGame(AA_Game *p_game);
        static AA_Game* GetGame();
        static void SetCurrentLevelId(int p_current_level_id);
        static int GetCurrentLevelId();
};