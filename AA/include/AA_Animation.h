#pragma once

#include <SDL3/SDL.h>
#include <string>
#include <vector>

class AA_Animation
{
    private:
    
        std::vector<SDL_Texture*> frames;
        int frame_speed;
        long unsigned int frame_counter = -1;

    public:

        AA_Animation(std::vector<std::string> frame_paths, int p_frame_speed);
        ~AA_Animation() = default;
        void Update();
        SDL_Texture* GetFrame();
        long unsigned int GetFrameCounterValue();
        int GetFrameSpeed();
        void Reset();
};