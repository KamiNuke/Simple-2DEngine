#include <iostream>

#include "Texture.h"
#include "globals.h"
#include "ResourceManager.h"

Texture::Texture()
{
}

bool Texture::LoadTexture(std::string path)
{
	texture = ResourceManager::Get().GetTexture(path);

	return (texture == nullptr) ? false : true;
}

void Texture::Render(const SDL_Rect* srcrect, const SDL_Rect* dstrect, const double angle, SDL_RendererFlip flip)
{
	if(SDL_RenderCopyEx(g_renderer, texture, srcrect, dstrect, angle, NULL, flip) < 0)
	{
		//std::cerr << "Couldn't render texture: " << SDL_GetError() << '\n';
	}
}
