// #include "AA_ConfigLoader.h"
// #include <fstream>
// #include <iostream>
// #include <SDL3/SDL.h>

// void AA_ConfigLoader::SetConfigFile(std::string config_file_path)
// {
//     std::fstream config;

//     config.open(config_file_path);

//     if(!config.is_open())
//         SDL_Log("\n\tAA_ConfigLoader::SetConfigFile()\t<< Could not open config file >>\n\n");
//     else
//     {
//         std::string line;
//         bool multiple_fields = false;

//         while(!config.eof())
//         {
//             getline(config, line);

//             std::cout<<line<<std::endl;
//         }
//     }
// }

// std::string AA_ConfigLoader::GetField(std::string field)
// {
    
// }