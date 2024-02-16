#pragma once
#include <SDL.h>
#include <unordered_map>
#include <iostream>
#include <string>

class ResourceManager
{
public:
	//If an instance exist then return it if not then create a new one
	static ResourceManager& Get()
	{
		if (s_instance == nullptr)
		{
			s_instance = new ResourceManager;
		}
		return *s_instance;
	}

	//Singleton does not need copy operator and copy constructor
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager operator=(const ResourceManager&) = delete;

	SDL_Texture* GetTexture(std::string path);

	//Get Key from value
	const char* GetKey(const SDL_Texture* tex) const;

	void UnloadTexture(std::string path);

	static void Destruct();
private:
	void CreateTexture(std::string path);

private:
	ResourceManager() = default;
	~ResourceManager() = default;
	static ResourceManager* s_instance;

	std::unordered_map<std::string, SDL_Texture*> map;
};

