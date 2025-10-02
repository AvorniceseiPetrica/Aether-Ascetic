#include "AA_Level.h"

#include "AA_RefLinks.h"
#include "AA_TextureLoader.h"
#include <fstream>

AA_Level::AA_Level(std::string p_map_path, std::string p_props_config_path, SDL_Point p_player_spawn, std::string p_layers_config)
{
    map_path = p_map_path;
    props_config_path = p_props_config_path;
    layers_config = p_layers_config;
    player_spawn = p_player_spawn;

    ghoul = new AA_Ghoul(500, 1540, 192, 192);
}

AA_Level::~AA_Level()
{

}

void AA_Level::Init()
{
    map.Init();
    map.LoadMap(map_path);

    std::fstream f;

    f.open(layers_config);

    if(!f.is_open())
        SDL_Log("\n\tAA_Level::Init()\t<< Cannot open config file: %s >>\n\n", layers_config.c_str());
    else
    {
        while(!f.eof())
        {
            std::string layer_texture_path;
            float layer_parallax;
            f>>layer_texture_path>>layer_parallax;

            layers.push_back(AA_TextureLoader::LoadTexture(layer_texture_path));
            layers_parallaxes.push_back(layer_parallax);

            SDL_Log("Read layer: %s | Parallax: %f", layer_texture_path.c_str(), layer_parallax);
        }
    }

    props.LoadProps(props_config_path);
    props.Init();

    AA_RefLinks::SetMap(&map);

    ghoul->Init();
    
    SDL_Log("Level initialized...\n");
}

void AA_Level::Update()
{
    // props don't have this functionality for now 

    // props.Update();
    
    ghoul->Update();
}

void AA_Level::Render()
{
    RenderLayers();

    props.Render();
    
    map.Render();

    //ghoul->Render();
}

void AA_Level::RenderLayers()
{
    float layer_width, layer_height;
    SDL_FRect dst;
    SDL_FRect camera = AA_RefLinks::GetCamera()->GetViewPort();

    for(int i = 0; i < layers.size(); i++)
    {
        SDL_GetTextureSize(layers[i], &layer_width, &layer_height);
        dst.x = -camera.x * layers_parallaxes[i];
        dst.y = -camera.y * layers_parallaxes[i] / 1.25;
        dst.w = layer_width;
        dst.h = layer_height;
        SDL_RenderTexture(AA_RefLinks::GetRenderer(), layers[i], nullptr, &dst);
    }
}

SDL_Point AA_Level::GetPlayerSpawn()
{
    return player_spawn;
}