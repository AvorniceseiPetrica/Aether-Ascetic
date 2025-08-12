#include "AA2_Map.h"

#include <fstream>
#include <SDL3/SDL.h>

AA2_Map::AA2_Map()
{
    for(int i = 0; i < TILEMAP_HEIGHT; i++)
        for(int j = 0; j < TILEMAP_WIDTH; j++)
            tilemap[i][j] = 0;
}

void AA2_Map::Init()
{
    tile_manager.Init();
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
                SDL_Log("i = %d | j = %d\n", i, j);
                f>>tilemap[i][j];   
                SDL_Log("Read: %d\n", tilemap[i][j]);
            }
    }

    f.close();
}

void AA2_Map::Render()
{
    int tile_x, tile_y;
    int tile_id;

    for(int i = 0; i < TILEMAP_HEIGHT; i++)
        for(int j = 0; j < TILEMAP_WIDTH; j++)
        {
            tile_x = j * TILE_WIDTH;
            tile_y = i * TILE_HEIGHT;
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