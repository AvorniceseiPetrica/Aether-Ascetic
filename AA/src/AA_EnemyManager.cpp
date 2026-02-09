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

        while(f>>enemy_type>>tile_x>>tile_y>>width>>height)
        {
            SDL_Log("Read enemy: enemy_type = %d, tile_x = %f, tile_y = %f, width = %f, height = %f", enemy_type, tile_x, tile_y, width, height);

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
     
        
        if(AA_RefLinks::GetPlayer()->GetCurrentState() == PLAYER_PUNCH || AA_RefLinks::GetPlayer()->GetCurrentState() == PLAYER_KICK)
        {
           SDL_FRect punch_hitbox = AA_RefLinks::GetPlayer()->GetAttackHitbox();

           if(SDL_HasRectIntersectionFloat(&punch_hitbox, &enemy_data))
           {
                if(AA_RefLinks::GetPlayer()->GetBodyHitbox()->x < enemy_data.x)
                    (*it)->TakeDamage(true);
                else
                    (*it)->TakeDamage(false);
           }
        }


        if (
            enemy_data.x < 0 ||
            enemy_data.x > TILEMAP_WIDTH * TILE_WIDTH - TILE_WIDTH ||
            enemy_data.y < 0 ||
            enemy_data.y > TILEMAP_HEIGHT * TILE_HEIGHT ||
            (*it)->IsDead()    
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