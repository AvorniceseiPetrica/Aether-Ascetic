#include "AA2_Map.h"

#include <fstream>
#include <SDL3/SDL.h>

#include "AA2_RefLinks.h"

AA2_Map::AA2_Map()
{
    for(int i = 0; i < TILEMAP_HEIGHT; i++)
        for(int j = 0; j < TILEMAP_WIDTH; j++)
            tilemap[i][j] = 0;
}

void AA2_Map::Init()
{
    tile_manager.Init();

    SDL_Log("Initialized map...\n");
}

void AA2_Map::LoadMap(std::string map_path)
{
    std::fstream f;

    f.open(map_path);

    if(!f.is_open())
        SDL_Log("\n\tAA2_Map::LoadMap()\t<< Could not open map config file >>\n\n");
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

void AA2_Map::Render()
{
    SDL_FRect camera = AA2_RefLinks::GetCamera()->GetViewPort();
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

void AA2_Map::PrintInfo()
{
    printf("TILEMAP_WIDTH = %d | TILEMAP_HEIGHT = %d\n", TILEMAP_WIDTH, TILEMAP_HEIGHT);
    for(int i = 0; i < TILEMAP_HEIGHT; i++)
    {
        for(int j = 0; j < TILEMAP_WIDTH; j++)
            printf("%d ", tilemap[i][j]);
        
        printf("\n");
    }
}

int AA2_Map::GetTileId(int x, int y)
{
    if(x < 0 || x >= TILEMAP_WIDTH || y < 0 || y >= TILEMAP_WIDTH)
        SDL_Log("\n\tAA2_Map::GetTileId()\t<< Invalid tile id >>\n\n");

    return tilemap[x][y];
}

bool AA2_Map::IsTileSolid(int id)
{
    return tile_manager.IsTileSolid(id);
}