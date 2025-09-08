#pragma once

#include <SDL3/SDL.h>
#include "AA2_Camera.h"
#include "AA2_Player.h"
#include "AA2_Map.h"

class AA2_RefLinks
{
    private:

        static SDL_Window *window;
        static SDL_Renderer *renderer;
        static AA2_Camera *camera;
        static AA2_Player *player;
        static AA2_Map *map;

    public:

        static void SetWindow(SDL_Window *p_window);
        static SDL_Window* GetWindow();
        static void SetRenderer(SDL_Renderer *p_renderer);
        static SDL_Renderer* GetRenderer();
        static void SetCamera(AA2_Camera *p_camera);
        static AA2_Camera* GetCamera();
        static void SetPlayer(AA2_Player *p_player);
        static AA2_Player* GetPlayer();
        static void SetMap(AA2_Map *p_map);
        static AA2_Map* GetMap();
};