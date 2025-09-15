#include "AA2_Game.h"

#include "AA2_RefLinks.h"
#include "AA2_TextureLoader.h"

#include "AA2_PlayState.h"

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

    SDL_SetRenderScale(renderer, 0.85, 0.85);

    SDL_Log("Created window and renderer..\n");
}

void AA2_Game::DestroySDL()
{
    if(renderer != nullptr)
        SDL_DestroyRenderer(renderer);
    
    if(window != nullptr)
        SDL_DestroyWindow(window);
}

void AA2_Game::Init(std::string window_name, int window_width, int window_height)
{
    InitSDL(window_name, window_width, window_height);
    SDL_SetRenderDrawColor(renderer, 0x21, 0x11, 0x55, 255);
    is_running = true;
    AA2_RefLinks::SetWindow(window);
    AA2_RefLinks::SetRenderer(renderer);

    ChangeState(new AA2_PlayState);

    SDL_Log("Initialized game...\n");
}

void AA2_Game::HandleEvents()
{
    SDL_Event e;

    while(SDL_PollEvent(&e))
    {
        if(e.type == SDL_EVENT_QUIT)
        {
            is_running = false;
            SDL_Log("User requested quitting...\n");
        }
    }
}

void AA2_Game::Update()
{
    current_state->Update();
}

void AA2_Game::Render()
{
    SDL_RenderClear(renderer);

    current_state->Render();

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

    DestroySDL();
}

void AA2_Game::ChangeState(AA2_State *new_state)
{
    if(new_state == nullptr)
        SDL_Log("New state is null");
    else
    {
        if(current_state != nullptr)
            delete current_state;
        
        current_state = new_state;
        current_state->Init();
    }
}