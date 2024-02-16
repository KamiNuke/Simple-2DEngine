#pragma once
#include <SDL.h>

#include "globals.h"
#include "constants.h"

class Camera
{
public:
	Camera(const int LEVEL_WIDTH, const int LEVEL_HEIGHT);

	void Update(const SDL_Rect player);
	//void ChangeScale();

	SDL_Rect GetRect() const { return cameraRect; }
private:
	SDL_Rect cameraRect{ 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT };
	int LEVEL_WIDTH, LEVEL_HEIGHT;
};

