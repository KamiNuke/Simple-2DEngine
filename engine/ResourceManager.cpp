#include <SDL_image.h>

#include "ResourceManager.h"
#include <iostream>
#include <globals.h>

//Static instance needs to be defined and initialized here
ResourceManager* ResourceManager::s_instance = nullptr;


SDL_Texture* ResourceManager::GetTexture(std::string path)
{
    //if there's no texture create a new one
    if (auto search = map.find(path); search == map.end())
    {
        CreateTexture(path);
    }

    return map[path];
}

const char* ResourceManager::GetKey(const SDL_Texture* tex) const
{
    for (auto search = map.begin(); search != map.end(); ++search)
    {
        if (search->second == tex) { return search->first.c_str(); }
    }

    return nullptr;
}

//IF YOU HAVE PROBLEMS WITH MEMORY LEAKS CHECK THIS FUNCTION!!!!
void ResourceManager::UnloadTexture(std::string path)
{
    //if the texture was found then delete it
    for (auto it = map.begin(); it != map.end();)
    {
        if (it->first == path)
        {
            SDL_DestroyTexture(it->second);
            it = map.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

//For memory leaks check this function
void ResourceManager::Destruct()
{
    //iterate through hash table
    for (auto& [key, value] : Get().map)
    {
        if (value != nullptr)
        {
            SDL_DestroyTexture(value);
        }
    }
    //clear entire map
    Get().map.clear();

    //Could cause memory leak because of static func
    delete s_instance;
    s_instance = nullptr;
}

void ResourceManager::CreateTexture(std::string path)
{
    SDL_Surface* tempSurface{ IMG_Load(path.c_str()) };

    //SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    if (tempSurface == nullptr)
    {
        std::cerr << "Couldn't create surface for texture: " << IMG_GetError() << '\n';
        return;
    }

    SDL_Texture* tempTexture{ SDL_CreateTextureFromSurface(g_renderer, tempSurface) };
    if (tempTexture == nullptr)
    {
        std::cerr << "Couldn't create texture from surface: " << SDL_GetError() << '\n';
        return;
    }

    SDL_FreeSurface(tempSurface);
    map[path] = tempTexture;
}
