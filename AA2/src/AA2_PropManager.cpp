#include "AA2_PropManager.h"

#include <fstream>

AA2_PropManager::AA2_PropManager(std::string p_props_config_path)
{
    props_config_path = p_props_config_path;
}

void AA2_PropManager::Init()
{
    for(auto prop : props)
        prop.Init();
}

void AA2_PropManager::LoadProps()
{
    std::fstream f;

    f.open(props_config_path);

    if(!f.is_open())
        SDL_Log("Could not open config path");
    else
        while(!f.eof())
        {   
            float x, y, width, height;
            std::string prop_texture_path;

            f>>x>>y>>width>>height>>prop_texture_path;

            props.push_back(AA2_Prop(x, y, width, height, prop_texture_path));
        }
}

void AA2_PropManager::Update()
{
    for(auto prop : props)
        prop.Update();
}

void AA2_PropManager::Render()
{
    for(auto prop : props)
        prop.Render();
}