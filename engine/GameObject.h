#pragma once
#include <SDL.h>

#include "IObject.h"
#include "Texture.h"

class GameObject : public IObject
{
public:

	GameObject(std::string path, int xPos, int yPos, int spriteWidth, int spriteHeight, int animationSprites);
	~GameObject();

	void Render(SDL_Rect camera);
	void ChangeFlip();

	void SetX(int x) { dstrect.x = x; }
	void SetY(int y) { dstrect.y = y; }

	SDL_Rect GetRect() { return dstrect; }

	std::string GetTexturePath() const { return texturePath; }
	int GetAnimationFrames() const { return animFrames; }
private:
	int animFrames{ 0 };
	Uint32 animationChangeTime{ SDL_GetTicks() };

	SDL_Rect dstrect{};
	SDL_Rect srcrect{};

	SDL_RendererFlip flip{ SDL_FLIP_NONE };
	Texture texture;
	std::string texturePath;
};

