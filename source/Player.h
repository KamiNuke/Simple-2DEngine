#pragma once

#include "Texture.h"
#include "Tile.h"

class Player
{
public:
	Player(std::string path, int xPos, int yPos,
		int spriteWidth, int spriteHeight, int animationSprites);
	~Player();

	void HandleEvent(SDL_Event& event);
	void Update(std::vector<Tile*>& tiles);
	void Move(std::vector<Tile*>& tiles);
	void Render(SDL_Rect camera);

	SDL_Rect GetRect() const { return dstrect; }

private:
	const int speed{ 10 };
	int animFrames{ 1 };
	bool isWalking{ false };
	Uint32 animationChangeTime{ SDL_GetTicks() };

	SDL_Rect dstrect{};
	SDL_Rect srcrect{};
	SDL_RendererFlip flip{ SDL_FLIP_NONE };
	Texture playerTexture;
	std::string texturePath{};
};

