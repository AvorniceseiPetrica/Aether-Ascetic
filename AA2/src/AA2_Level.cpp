#include "AA2_Level.h"

#include "AA2_RefLinks.h"
#include "AA2_TextureLoader.h"

AA2_Level::AA2_Level(std::string p_map_path, std::string p_props_config_path, SDL_Point p_player_spawn)
{
    map_path = p_map_path;
    props_config_path = p_props_config_path;
    background_path = "assets/backgrounds/background.png";
    midground1_path = "assets/backgrounds/midground.png";
    midground2_path = "assets/backgrounds/midground2.png";
    player_spawn = p_player_spawn;
}

AA2_Level::~AA2_Level()
{

}

void AA2_Level::Init()
{
    map.Init();
    map.LoadMap(map_path);

    background = AA2_TextureLoader::LoadTexture(background_path);
    midground1 = AA2_TextureLoader::LoadTexture(midground1_path);
    midground2 = AA2_TextureLoader::LoadTexture(midground2_path);

    props.LoadProps(props_config_path);
    props.Init();

    AA2_RefLinks::SetMap(&map);
    
    SDL_Log("Level initialized...\n");
}

void AA2_Level::Update()
{
    props.Update();
}

void AA2_Level::Render()
{
    RenderBackground();
    RenderMidground1();
    RenderMidground2();
        
    props.Render();
    
    map.Render();
}

void AA2_Level::RenderBackground()
{
    float background_width, background_height;

    SDL_GetTextureSize(background, &background_width, &background_height);

    SDL_FRect camera = AA2_RefLinks::GetCamera()->GetViewPort();
    SDL_FRect background_rect = {
        .x = -camera.x * background_parallax,
        .y = -camera.y * background_parallax,
        .w = background_width,
        .h = background_height
    };

    SDL_RenderTexture(AA2_RefLinks::GetRenderer(), background, nullptr, &background_rect);
}

void AA2_Level::RenderMidground1()
{
    float midground_width, midground_height;

    SDL_GetTextureSize(midground1, &midground_width, &midground_height);

    SDL_FRect camera = AA2_RefLinks::GetCamera()->GetViewPort();
    SDL_FRect midground_rect = {
        .x = -camera.x * midground1_parallax,
        .y = -camera.y * midground1_parallax,
        .w = midground_width,
        .h = midground_height
    };

    SDL_RenderTexture(AA2_RefLinks::GetRenderer(), midground1, nullptr, &midground_rect);
}

void AA2_Level::RenderMidground2()
{
    float midground_width, midground_height;

    SDL_GetTextureSize(midground2, &midground_width, &midground_height);

    SDL_FRect camera = AA2_RefLinks::GetCamera()->GetViewPort();
    SDL_FRect midground_rect = {
        .x = -camera.x * midground2_parallax,
        .y = -camera.y * midground2_parallax,
        .w = midground_width,
        .h = midground_height
    };

    SDL_RenderTexture(AA2_RefLinks::GetRenderer(), midground2, nullptr, &midground_rect);
}

SDL_Point AA2_Level::GetPlayerSpawn()
{
    return player_spawn;
}