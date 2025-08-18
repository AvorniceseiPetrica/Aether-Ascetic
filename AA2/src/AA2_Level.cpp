#include "AA2_Level.h"

#include "AA2_RefLinks.h"
#include "AA2_TextureLoader.h"

AA2_Level::AA2_Level(std::string p_map_path, SDL_Point player_spawn) : player(player_spawn.x, player_spawn.y)
{
    map_path = p_map_path;
    background_path = "assets/backgrounds/background.png";
    midground_path = "assets/backgrounds/midground.png";
}

AA2_Level::~AA2_Level()
{

}

void AA2_Level::Init()
{
    map.Init();
    map.LoadMap(map_path);

    player.Init();
    AA2_RefLinks::SetPlayer(&player);

    background = AA2_TextureLoader::LoadTexture(background_path);
    midground = AA2_TextureLoader::LoadTexture(midground_path);
}

void AA2_Level::Update()
{
    player.Update();
}

void AA2_Level::Render()
{
    RenderBackground();
    RenderMidground();
    
    map.Render();

    player.Render();
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

void AA2_Level::RenderMidground()
{
    float midground_width, midground_height;

    SDL_GetTextureSize(midground, &midground_width, &midground_height);

    SDL_FRect camera = AA2_RefLinks::GetCamera()->GetViewPort();
    SDL_FRect midground_rect = {
        .x = -camera.x * midground_parallax,
        .y = -camera.y * midground_parallax,
        .w = midground_width,
        .h = midground_height
    };

    SDL_RenderTexture(AA2_RefLinks::GetRenderer(), midground, nullptr, &midground_rect);
}