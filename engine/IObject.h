#pragma once

#include <SDL.h>

class IObject
{
public:
	IObject() {}
	virtual void Render(SDL_Rect camera) = 0;
	virtual void SetX(int x) = 0;
	virtual void SetY(int y) = 0;
	virtual SDL_Rect GetRect() = 0;
};