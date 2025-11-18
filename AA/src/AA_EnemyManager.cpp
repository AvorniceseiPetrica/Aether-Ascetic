#include "AA_EnemyManager.h"

#include <fstream>
#include "AA_Ghoul.h"
#include "AA_Wizard.h"
#include "AA_Config.h"
#include "AA_RefLinks.h"

AA_EnemyManager::AA_EnemyManager()
{
    
}

AA_EnemyManager::~AA_EnemyManager()
{
    for(auto enemy : enemies)
        if(enemy != nullptr)
            delete enemy;
}

void AA_EnemyManager::LoadEnemies(std::string enemies_config_path)
{
    std::fstream f;

    f.open(enemies_config_path);

    if(!f.is_open())
        SDL_Log("\n\tAA_EnemyManager::LoadEnemies()\t<< Could not open config file %s >>\n\n", enemies_config_path.c_str());
    else
    {
        int enemy_type;
        float tile_x, tile_y, width, height;

        while(!f.eof())
        {
            f>>enemy_type>>tile_x>>tile_y>>width>>height;

            switch(enemy_type)
            {
                case ENEMY_GHOUL: enemies.push_back(new AA_Ghoul(tile_x * TILE_WIDTH, tile_y * TILE_HEIGHT, width, height, 3));
                break;

                case ENEMY_WIZARD: enemies.push_back(new AA_Wizard(tile_x * TILE_WIDTH, tile_y * TILE_HEIGHT, width, height, 2));
                break;
            }
        }
    }

    SDL_Log("Enemies loaded...\n");
}

void AA_EnemyManager::InitEnemies()
{
    for(auto &enemy : enemies)
        enemy->Init();

    SDL_Log("Enemies initialized...\n");
}

void AA_EnemyManager::UpdateEnemies()
{
    for(auto &enemy : enemies)
        enemy->Update();

    for (auto it = enemies.begin(); it != enemies.end();)
    {
        SDL_FRect enemy_data = (*it)->GetData();
        bool dead_enemy = false;
         int current_player_state = AA_RefLinks::GetPlayer()->GetCurrentState();

        if(current_player_state == PLAYER_PUNCH)
        {
            SDL_FRect punch_hitbox = AA_RefLinks::GetPlayer()->GetPunchHitbox();

            SDL_Log("punch hitbox: %f, %f, %f, %f\n", punch_hitbox.x, punch_hitbox.y, punch_hitbox.w, punch_hitbox.h);
            SDL_Log("enemy data: %f, %f, %f, %f\n", enemy_data.x, enemy_data.y, enemy_data.w, enemy_data.h);
            SDL_Log("intersection: %d\n", SDL_HasRectIntersectionFloat(&punch_hitbox, &enemy_data));

            if(SDL_HasRectIntersectionFloat(&punch_hitbox, &enemy_data))
            {
                dead_enemy = true;
                
                SDL_Log("Player punched smth at: %f, %f\n", punch_hitbox.x, punch_hitbox.y);
            }
        }

        if (
            enemy_data.x < 0 ||
            enemy_data.x > TILEMAP_WIDTH * TILE_WIDTH - TILE_WIDTH ||
            enemy_data.y < 0 ||
            enemy_data.y > TILEMAP_HEIGHT * TILE_HEIGHT ||
            (*it)->GetHealth() == 0 ||
            dead_enemy == true
            )
        {
            delete *it;
            it = enemies.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void AA_EnemyManager::RenderEnemies()
{
    for(auto &enemy : enemies)
        enemy->Render();
}