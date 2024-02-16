#include "Tile.h"

#include "globals.h"
#include "LevelFunctions.h"
#include "constants.h"
#include <iostream>

Tile::Tile(int x, int y, TileType type, int animFrames)
{
	this->type = type;
	rect.x = x;
	rect.y = y;
	rect.w = TILE_WIDTH;
	rect.h = TILE_HEIGHT;

	srcrect.x = 0;
	srcrect.y = 0;
	srcrect.w = TILE_WIDTH;
	srcrect.h = TILE_HEIGHT;

	this->animFrames = animFrames;
}

Tile::Tile(std::string path, int x, int y, TileType type, int animFrames)
{
	this->type = type;
	rect.x = x;
	rect.y = y;
	rect.w = TILE_WIDTH;
	rect.h = TILE_HEIGHT;

	srcrect.x = 0;
	srcrect.y = 0;
	srcrect.w = TILE_WIDTH;
	srcrect.h = TILE_HEIGHT;

	this->animFrames = animFrames;

	texture = new Texture{};
	if (!texture->LoadTexture(path))
	{
		delete texture;
		texture = nullptr;
	}
}

Tile::~Tile()
{
	delete texture;
}

void Tile::Render(SDL_Rect camera)
{
	SDL_Rect cameraRect{ rect.x - camera.x, rect.y - camera.y, rect.w, rect.h };
	if (texture != nullptr)
	{
		//render tiles ONLY if they on the screen
		if (CheckCollision(camera, rect))
		{
			texture->Render(&srcrect, &cameraRect);

			if (isHitbox)
			{
				cameraRect.x += 2;
				cameraRect.y += 2;
				cameraRect.w = 28;
				cameraRect.h = 28;
				SDL_RenderDrawRect(g_renderer, &cameraRect);
			}
		}
		
		//If passed 0.4s then play next animation
		if (animationChangeTime + 400 < SDL_GetTicks())
		{
			if (srcrect.x >= (srcrect.w * (animFrames - 1)))
			{
				srcrect.x = 0;

			}
			else
			{
				srcrect.x += rect.w;
			}

			animationChangeTime = SDL_GetTicks();
		}

	}
	else
	{
		//render tiles ONLY if they on the screen
		if (CheckCollision(camera, rect))
		{
			SDL_RenderDrawRect(g_renderer, &cameraRect);

			if (isHitbox)
			{
				cameraRect.x += 2;
				cameraRect.y += 2;
				cameraRect.w = 28;
				cameraRect.h = 28;
				SDL_RenderDrawRect(g_renderer, &cameraRect);
			}
		}	
	}	
}

SDL_Rect Tile::GetRect()
{
	return rect;
}

const char* Tile::GetPath() const
{
	return ResourceManager::Get().GetKey(texture->GetTexture());
}
