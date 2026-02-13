#include "AA_WinState.h"
#include "AA_TextureLoader.h"
#include "AA_RefLinks.h"
#include "AA_PlayState.h"

enum BUTTONS {
    START_GAME,
    QUIT_GAME
};

void AA_WinState::Init()
{
    background = AA_TextureLoader::LoadTexture("assets/menu/win_menu_background.png");
    start_game_button_unpressed = AA_TextureLoader::LoadTexture("assets/menu/start_game.png");
    start_game_button_pressed = AA_TextureLoader::LoadTexture("assets/menu/start_game_pressed.png");
    quit_game_button_unpressed = AA_TextureLoader::LoadTexture("assets/menu/quit_game.png");
    quit_game_button_pressed = AA_TextureLoader::LoadTexture("assets/menu/quit_game_pressed.png");

    start_game_pressed = false;
    quit_game_pressed = false;

    AA_MenuButton start_game_button = AA_MenuButton(
        WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2,
        WINDOW_HEIGHT / 2 - 100,
        BUTTON_WIDTH,
        BUTTON_HEIGHT,
        "assets/menu/start_game.png",
        "assets/menu/start_game_pressed.png"
    );
    AA_MenuButton quit_game_button = AA_MenuButton(
        WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2,
        WINDOW_HEIGHT / 2 + 200,
        BUTTON_WIDTH,
        BUTTON_HEIGHT,
        "assets/menu/quit_game.png",
        "assets/menu/quit_game_pressed.png"
    );

    buttons.push_back(start_game_button);
    buttons.push_back(quit_game_button);
    
    SDL_SetRenderScale(AA_RefLinks::GetRenderer(), 1, 1);

    SDL_Log("GameOverState initialized...\n");
}

void AA_WinState::HandleEvents()
{
    SDL_Event e;

    while(SDL_PollEvent(&e))
    {
        if(e.type == SDL_EVENT_QUIT)
        {
            exit(0);
            return;
        }

        if(e.type == SDL_EVENT_KEY_DOWN)
        {
            switch(e.key.scancode)
            {
                case SDL_SCANCODE_DOWN:
                {
                    if(current_button_index == buttons.size() - 1)
                        current_button_index = 0;
                    else
                        current_button_index++;
                }
                break;

                case SDL_SCANCODE_UP:
                {
                    if(current_button_index == 0)
                        current_button_index = buttons.size() - 1;
                    else
                        current_button_index--;
                }
                break;

                case SDL_SCANCODE_RETURN:
                {
                    switch(current_button_index)
                    {
                        case START_GAME:
                        {
                            AA_RefLinks::GetGame()->ChangeState(new AA_PlayState);
                        }
                        break;

                        case QUIT_GAME:
                        {
                            exit(0);
                        }
                        break;
                    }
                }

                default: break;
            }
        }
    }
}

void AA_WinState::Update()
{
    for(auto& button : buttons)
        button.SetIfPressed(false);

    buttons[current_button_index].SetIfPressed(true);
}

void AA_WinState::Render()
{
    SDL_RenderTexture(AA_RefLinks::GetRenderer(), background, nullptr, &background_rect);
    
    for(auto button :  buttons)
        button.Render();
}