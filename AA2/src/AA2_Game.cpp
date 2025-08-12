#include "AA2_Game.h"

#include "AA2_RefLinks.h"
#include "AA2_TextureLoader.h"
#include "AA2_Map.h"

SDL_Texture *txt;
SDL_FRect dst = {
    .x = 100,
    .y = 100,
    .w = 100,
    .h = 100    
};

AA2_Map M;

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
    SDL_SetRenderDrawColor(renderer, 0x21, 0x11, 0x55, 255);
    is_running = true;
    AA2_RefLinks::SetWindow(window);
    AA2_RefLinks::SetRenderer(renderer);

    txt = AA2_TextureLoader::LoadTexture("assets/textures/pixel.png");
    M.Init();
    M.LoadMap("configs/map.txt");
    M.PrintInfo();
}

void AA2_Game::HandleEvents()
{
    SDL_Event e;

    while(SDL_PollEvent(&e))
    {
        if(e.type == SDL_EVENT_QUIT)
            is_running = false;
    }
}

void AA2_Game::Update()
{
    dst.x += 1;
}

void AA2_Game::Render()
{
    SDL_RenderClear(renderer);

    SDL_RenderTexture(renderer, txt, nullptr, &dst);
    M.Render();

    SDL_RenderPresent(renderer);
}

void AA2_Game::Run()
{
    int current_frame_start;
    int current_frame_end;
    int current_frame_time;
    int FPS = 60;
    int target_frame_time = 1000 / FPS;

    while(is_running)
    {
        current_frame_start = SDL_GetTicks();
        HandleEvents();
        Update();
        Render();
        current_frame_end = SDL_GetTicks();
        current_frame_time = current_frame_end - current_frame_start;

        if(current_frame_time < target_frame_time)
            SDL_Delay(target_frame_time - current_frame_time);
    }
}