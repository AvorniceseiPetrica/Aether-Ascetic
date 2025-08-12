#include "AA2_Game.h"

void AA2_Game::InitSDL(std::string window_name, int window_width, int window_height)
{
    if(!SDL_Init(SDL_INIT_VIDEO))
        SDL_Log("\n\t<< Failed to initialize video subsystems >>\n\n");
    else
    {
        window = SDL_CreateWindow(window_name.c_str(), window_width, window_height, 0);

        if(window == nullptr)
            SDL_Log("\n\t<< Could not create window >>\n\n");
        else
        {
            renderer = SDL_CreateRenderer(window, nullptr);

            if(renderer == nullptr)
                SDL_Log("\n\t<< Could not create renderer >>\n\n");
        }
    }
}

void AA2_Game::Init(std::string window_name, int window_width, int window_height)
{
    InitSDL(window_name, window_width, window_height);
    is_running = true;
}

void AA2_Game::Update()
{
    std::cout<<"a\n";
}

void AA2_Game::Render()
{
    SDL_RenderClear(renderer);

    // render here

    SDL_RenderPresent(renderer);
}

void AA2_Game::Run()
{
    while(is_running)
    {
        SDL_Event e;

        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_EVENT_QUIT)
                is_running = false;
            else
            {
                Update();
                Render();
            }
        }
    }
}