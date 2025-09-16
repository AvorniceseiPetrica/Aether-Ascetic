#include "AA_RefLinks.h"

SDL_Window *AA_RefLinks::window = nullptr;
SDL_Renderer *AA_RefLinks::renderer = nullptr;
AA_Camera *AA_RefLinks::camera = nullptr;
AA_Player *AA_RefLinks::player = nullptr;
AA_Map *AA_RefLinks::map = nullptr;
AA_Game *AA_RefLinks::game = nullptr;

void AA_RefLinks::SetWindow(SDL_Window *p_window)
{
    if(p_window == nullptr)
        SDL_Log("\n\tAA_RefLinks::SetWindow()\t<< Provided NULL for (SDL_Window *p_window) >>\n\n");
    else
        window = p_window;
}

SDL_Window* AA_RefLinks::GetWindow()
{
    return window;
}

void AA_RefLinks::SetRenderer(SDL_Renderer *p_renderer)
{
    if(p_renderer == nullptr)
        SDL_Log("\n\tAA_RefLinks::SetRenderer()\t<< Provided NULL for (SDL_Renderer *p_renderer) >>\n\n");
    else
        renderer = p_renderer;
}

SDL_Renderer* AA_RefLinks::GetRenderer()
{
    return renderer;
}

void AA_RefLinks::SetCamera(AA_Camera *p_camera)
{
    if(p_camera == nullptr)  
        SDL_Log("\n\tAA_RefLinks::SetCamera()\t<< Provided NULL for (AA_Camera *p_camera) >>\n\n");
    else
        camera = p_camera;
}

AA_Camera* AA_RefLinks::GetCamera()
{
    return camera;
}

void AA_RefLinks::SetPlayer(AA_Player *p_player)
{
    if(p_player == nullptr)  
        SDL_Log("\n\tAA_RefLinks::SetPlayer()\t<< Provided NULL for (AA_Player *p_player) >\n\n");
    else
        player = p_player;
}

AA_Player* AA_RefLinks::GetPlayer()
{
    return player;
}

void AA_RefLinks::SetMap(AA_Map *p_map)
{
    if(p_map == nullptr)  
        SDL_Log("\n\tAA_RefLinks::SetMap()\t<< Provided NULL for (AA_Map *p_map) >\n\n");
    else
        map = p_map;
}

AA_Map* AA_RefLinks::GetMap()
{
    return map;
}

void AA_RefLinks::SetGame(AA_Game *p_game)
{
    if(p_game == nullptr)  
        SDL_Log("\n\tAA_RefLinks::SetGame()\t<< Provided NULL for (AA_Game *p_game) >\n\n");
    else
        game = p_game;
}

AA_Game* AA_RefLinks::GetGame()
{
    return game;
}