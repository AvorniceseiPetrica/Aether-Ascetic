#include "AA_Animation.h"
#include "AA_TextureLoader.h"

AA_Animation::AA_Animation(std::vector<std::string> frame_paths, int p_frame_speed)
{
    if(p_frame_speed <= 0)
    {
        SDL_Log("\n\tAA_Animation::AA_Animation()\t<< Invalid frame_speed >>\n\n");
        frame_speed = 1;
    }
    else
        frame_speed = p_frame_speed;

    for(auto frame_path : frame_paths)
    {
        SDL_Texture *frame = AA_TextureLoader::LoadTexture(frame_path);

        frames.push_back(frame);
    }
}

void AA_Animation::Update()
{
    frame_counter++;

    if(frame_counter >= frames.size() * frame_speed)
        frame_counter = 0;  
}

SDL_Texture* AA_Animation::GetFrame()
{
    SDL_Log("%d", frame_counter);
    return frames[frame_counter / frame_speed];
}

long unsigned int AA_Animation::GetFrameCounterValue()
{
    return frame_counter;
}

int AA_Animation::GetFrameSpeed()
{
    return frame_speed;
}

void AA_Animation::Reset()
{
    frame_counter = -1;
}