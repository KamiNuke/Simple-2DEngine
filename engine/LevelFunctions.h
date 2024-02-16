#pragma once
#include <SDL.h>

#include "Tile.h"
#include "GameObject.h"

bool CheckCollision(const SDL_Rect A, const SDL_Rect B);


void SaveLevel(std::string levelName, std::vector<Tile*>& tiles, std::vector<GameObject*>& gameobject);

void LoadLevel(std::string levelName, std::vector<Tile*>& tiles, std::vector<GameObject*>& gameobject);