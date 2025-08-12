#include "AA2_RefLinks.h"

SDL_Window *AA2_RefLinks::window = nullptr;
SDL_Renderer *AA2_RefLinks::renderer = nullptr;

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