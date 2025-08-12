#pragma once

#include <SDL3/SDL.h>

class AA2_RefLinks
{
    private:

        static SDL_Window *window;
        static SDL_Renderer *renderer;

    public:

        static void SetWindow(SDL_Window *p_window);
        static SDL_Window* GetWindow();
        static void SetRenderer(SDL_Renderer *p_renderer);
        static SDL_Renderer* GetRenderer();
};