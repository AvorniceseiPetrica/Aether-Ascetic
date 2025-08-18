#include "AA2_RefLinks.h"

SDL_Window *AA2_RefLinks::window = nullptr;
SDL_Renderer *AA2_RefLinks::renderer = nullptr;
AA2_Camera *AA2_RefLinks::camera = nullptr;
AA2_Player *AA2_RefLinks::player = nullptr;

void AA2_RefLinks::SetWindow(SDL_Window *p_window)
{
    if(p_window == nullptr)
        SDL_Log("\n\tAA2_RefLinks::SetWindow()\t<< Provided NULL for (SDL_Window *p_window) >>\n\n");
    else
        window = p_window;
}

SDL_Window* AA2_RefLinks::GetWindow()
{
    return window;
}

void AA2_RefLinks::SetRenderer(SDL_Renderer *p_renderer)
{
    if(p_renderer == nullptr)
        SDL_Log("\n\tAA2_RefLinks::SetRenderer()\t<< Provided NULL for (SDL_Renderer *p_renderer) >>\n\n");
    else
        renderer = p_renderer;
}

SDL_Renderer* AA2_RefLinks::GetRenderer()
{
    return renderer;
}

void AA2_RefLinks::SetCamera(AA2_Camera *p_camera)
{
    if(p_camera == nullptr)  
        SDL_Log("\n\tAA2_RefLinks::SetCamera()\t<< Provided NULL for (AA2_Camera *camera) >>\n\n");
    else
        camera = p_camera;
}

AA2_Camera* AA2_RefLinks::GetCamera()
{
    return camera;
}

void AA2_RefLinks::SetPlayer(AA2_Player *p_player)
{
    if(p_player == nullptr)  
        SDL_Log("\n\tAA2_RefLinks::SetPlayer()\t<< Provided NULL for (AA2_Player *player) >\n\n");
    else
        player = p_player;
}

AA2_Player* AA2_RefLinks::GetPlayer()
{
    return player;
}