#include "AA_Map.h"

#include <fstream>
#include <SDL3/SDL.h>

#include "AA_RefLinks.h"
#include "AA_Config.h"

AA_Map::AA_Map()
{
    for(int i = 0; i < TILEMAP_HEIGHT; i++)
        for(int j = 0; j < TILEMAP_WIDTH; j++)
            tilemap[i][j] = 0;
}

void AA_Map::Init()
{
    tile_manager.Init();

    SDL_Log("Initialized map...\n");
}

void AA_Map::LoadMap(std::string map_path)
{
    std::fstream f;

    f.open(map_path);

    if(!f.is_open())
        SDL_Log("\n\tAA_Map::LoadMap()\t<< Could not open config file >>\n\n");
    else
    {
        for(int i = 0; i < TILEMAP_HEIGHT; i++)
            for(int j = 0; j < TILEMAP_WIDTH; j++)
            {
                f>>tilemap[i][j];   
            }
    }

    f.close();

    SDL_Log("Loaded map: %s...\n", map_path.c_str());
}

void AA_Map::Render()
{
    SDL_FRect camera = AA_RefLinks::GetCamera()->GetViewPort();
    int tile_x, tile_y;
    int tile_id;

    for(int i = 0; i < TILEMAP_HEIGHT; i++)
        for(int j = 0; j < TILEMAP_WIDTH; j++)
        {
            tile_x = j * TILE_WIDTH - camera.x;
            tile_y = i * TILE_HEIGHT - camera.y;
            tile_id = tilemap[i][j];
            
            tile_manager.GetTile(tile_id)->Render(tile_x, tile_y);
        }
}

void AA_Map::PrintInfo()
{
    printf("TILEMAP_WIDTH = %d | TILEMAP_HEIGHT = %d\n", TILEMAP_WIDTH, TILEMAP_HEIGHT);
    for(int i = 0; i < TILEMAP_HEIGHT; i++)
    {
        for(int j = 0; j < TILEMAP_WIDTH; j++)
            printf("%d ", tilemap[i][j]);
        
        printf("\n");
    }
}

int AA_Map::GetTileId(int x, int y)
{
    if(x < 0 || x >= TILEMAP_WIDTH || y < 0 || y >= TILEMAP_HEIGHT)
        SDL_Log("\n\tAA_Map::GetTileId()\t<< Invalid tile coords | x = %d | y = %d >>\n\n", x, y);

    return tilemap[y][x];
}

bool AA_Map::IsTileSolid(int id)
{
    return tile_manager.IsTileSolid(id);
}