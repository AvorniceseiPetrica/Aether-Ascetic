#include "AA2_Game.h"

#include "AA2_RefLinks.h"
#include "AA2_TextureLoader.h"
#include "AA2_Map.h"
#include "AA2_Player.h"
#include "AA2_Camera.h"
#include "AA2_Level.h"

AA2_Level L("configs/map0.txt", {.x = 200, .y = 1000});
AA2_Camera C;

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
    AA2_RefLinks::SetCamera(&C);

    L.Init();
    C.SetTarget(AA2_RefLinks::GetPlayer()->GetRect());

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
    L.Update();
    C.Update();
}

void AA2_Game::Render()
{
    SDL_RenderClear(renderer);

    L.Render();
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