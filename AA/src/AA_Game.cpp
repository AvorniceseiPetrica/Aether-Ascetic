#include "AA_Game.h"

#include "AA_RefLinks.h"
#include "AA_TextureLoader.h"

#include "AA_PlayState.h"
#include "AA_MenuState.h"

void AA_Game::InitSDL(std::string window_name, int window_width, int window_height)
{
    if(!SDL_Init(SDL_INIT_VIDEO))
        SDL_Log("\n\tAA_Game::InitSDL()\t<< Failed to initialize video subsystems >>\n\n");
    else
    {
        window = SDL_CreateWindow(window_name.c_str(), window_width, window_height, 0);

        if(window == nullptr)
            SDL_Log("\n\tAA_Game::InitSDL()\t<< Could not create window >>\n\n");
        else
        {
            renderer = SDL_CreateRenderer(window, nullptr);

            if(renderer == nullptr)
                SDL_Log("\n\tAA_Game::InitSDL()\t<< Could not create renderer >>\n\n");
        }
    }

    SDL_Log("Created window and renderer..\n");
}

void AA_Game::DestroySDL()
{
    if(renderer != nullptr)
        SDL_DestroyRenderer(renderer);
    
    if(window != nullptr)
        SDL_DestroyWindow(window);
}

void AA_Game::Init(std::string window_name, int window_width, int window_height)
{
    InitSDL(window_name, window_width, window_height);
    is_running = true;
    AA_RefLinks::SetWindow(window);
    AA_RefLinks::SetRenderer(renderer);
    AA_RefLinks::SetGame(this);

    ChangeState(new AA_MenuState);

    SDL_Log("Initialized game...\n");
}

void AA_Game::HandleEvents()
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

void AA_Game::Update()
{
    if(current_state != nullptr)
        current_state->Update();
    
    if(next_state != nullptr)
    {
        if(current_state != nullptr)
            delete current_state;

        current_state = next_state;
        current_state->Init();
        next_state = nullptr;
    }
}

void AA_Game::Render()
{
    SDL_RenderClear(renderer);

    current_state->Render();

    SDL_RenderPresent(renderer);
}

void AA_Game::Run()
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

void AA_Game::ChangeState(AA_State *new_state)
{
    if(new_state == nullptr)
        SDL_Log("\n\tAA_Game::ChangeState()\t<< Providede NULL for (AA_State *new_state) >>");
    else
        next_state = new_state;
}