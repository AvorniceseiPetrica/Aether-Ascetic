#include "AA_PropManager.h"

#include <fstream>

void AA_PropManager::Init()
{
    for(auto& prop : props)
        prop.Init();
}

void AA_PropManager::LoadProps(std::string props_config_path)
{
    std::fstream f;

    f.open(props_config_path);

    if(!f.is_open())
        SDL_Log("\n\tAA_PropManager::LoadProps()\t<< Could not open config file >>\n\n");
    else
        while(!f.eof())
        {   
            float x, y, width, height;
            std::string prop_texture_path;

            f>>x>>y>>width>>height>>prop_texture_path;

            props.push_back(AA_Prop(x, y, width, height, prop_texture_path));
            //SDL_Log("Loaded prop: %s, %f, %f\n", prop_texture_path.c_str(), x, y);
        }

    SDL_Log("Loaded props: %s...", props_config_path.c_str());
}

void AA_PropManager::Update()
{
    for(auto& prop : props)
        prop.Update();
}

void AA_PropManager::Render()
{
    for(auto& prop : props)
        prop.Render();
}