#include "GameObject.h"
#include "globals.h"
#include "LevelFunctions.h"
#include "ResourceManager.h"

GameObject::GameObject(std::string path, int xPos, int yPos,
	int spriteWidth, int spriteHeight, int animationSprites)
{
	dstrect.x = xPos;
	dstrect.y = yPos;
	dstrect.w = spriteWidth;
	dstrect.h = spriteHeight;

	srcrect.x = 0;
	srcrect.y = 0;
	srcrect.w = spriteWidth;
	srcrect.h = spriteHeight;

	animFrames = animationSprites;

	texture.LoadTexture(path);
	texturePath = path;
}

GameObject::~GameObject()
{
	//ResourceManager::Get().UnloadTexture(texturePath);
}

void GameObject::Render(SDL_Rect camera)
{
	//Create rect depending on camera
	SDL_Rect cameraRect{ dstrect.x - camera.x, dstrect.y - camera.y,  dstrect.w,  dstrect.h };

	if (CheckCollision(camera, dstrect))
	{
		texture.Render(&srcrect, &cameraRect, 0, flip);

		if (isHitbox)
		{
			SDL_SetRenderDrawColor(g_renderer, 0, 0xFF, 0, 0xFF);
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
			srcrect.x += dstrect.w;
		}

		animationChangeTime = SDL_GetTicks();
	}

}

void GameObject::ChangeFlip()
{
	if (flip == SDL_FLIP_NONE)
	{
		flip = SDL_FLIP_HORIZONTAL;
	}
	else
	{
		flip = SDL_FLIP_NONE;
	}
}