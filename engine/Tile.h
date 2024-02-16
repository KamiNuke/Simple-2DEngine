#pragma once

#include "IObject.h"
#include "Texture.h"

#include "ResourceManager.h"

enum class TileType
{
	BREAKABLE,
	UNBREAKABLE,

	MAX_TYPES
};

class Tile : public IObject
{
public:
	Tile(int x, int y, TileType type, int animFrames = 0);
	Tile(std::string path, int x, int y, TileType type, int animFrames = 0);
	~Tile();


	void Render(SDL_Rect camera);

	void SetX(int x) { rect.x = x; }
	void SetY(int y) { rect.y = y; }
	SDL_Rect GetRect();
	TileType GetType() const { return type; }

	const char* GetPath() const;
	int GetAnimationFrames() const { return animFrames; }
private:
	SDL_Rect rect{};
	SDL_Rect srcrect{};
	Uint32 animationChangeTime{ SDL_GetTicks() };
	int animFrames{ 0 };

	Texture* texture{ nullptr };
	TileType type;
};

