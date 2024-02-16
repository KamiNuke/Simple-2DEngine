#pragma once
#include <SDL.h>
#include <unordered_map>
#include <string>

class Texture
{
public:
	Texture();

	bool LoadTexture(std::string path);

	void Render(const SDL_Rect* srcrect = nullptr, const SDL_Rect* dstrect = nullptr, const double angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	const SDL_Texture* GetTexture() const { return texture; }
private:
	SDL_Texture* texture{ nullptr };
};

