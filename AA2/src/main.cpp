#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

int main()
{
    if(!SDL_Init(SDL_INIT_VIDEO))
        SDL_Log("\n\t<< Failed to initialize video subsystems >>\n\n");
    else
    {
        SDL_Window *window = SDL_CreateWindow("AA2", 1920, 1080, 0);

        if(window == nullptr)
            SDL_Log("\n\t<< Could not create window >>\n\n");
        else
        {
            SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

            if(renderer == nullptr)
                SDL_Log("\n\t<< Could not create renderer >>\n\n");
            else
            {
                SDL_Event e;
                bool quit = false; 

                while( quit == false )
                { 
                    while( SDL_PollEvent( &e ) )
                    { 
                        if( e.type == SDL_EVENT_QUIT ) 
                            quit = true; 
                        SDL_SetRenderDrawColor(renderer, 0xaa, 0xbb, 0xcc, 255);
                        SDL_FRect dst = {
                            .x = 100, 
                            .y = 100, 
                            .w = 100, 
                            .h = 100
                        };
                        
                        SDL_RenderRect(renderer, &dst);
                        SDL_UpdateWindowSurface(window);
                        SDL_RenderPresent(renderer);
                    } 
                }
            }

        }
    }
}