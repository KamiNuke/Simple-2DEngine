#include "Camera.h"

#include "constants.h"
#include <iostream>

Camera::Camera(const int LEVEL_WIDTH, const int LEVEL_HEIGHT)
{
	//Set camera limit to level size 
	this->LEVEL_WIDTH = LEVEL_WIDTH;
	this->LEVEL_HEIGHT = LEVEL_HEIGHT;
}

void Camera::Update(const SDL_Rect player)
{
	//for 1280x720 with x2 render scale
	//cameraRect.x = (player.x + 350 - player.w / 2) - (LOGICAL_WIDTH / 2);
	//cameraRect.y = (player.y + 220 - player.h / 2) - (LOGICAL_HEIGHT / 2);
	
	
	//for 1280x720 without render scale
	cameraRect.x = (player.x + 32 - player.w / 2) - (LOGICAL_WIDTH / 2);
	cameraRect.y = (player.y + 20 - player.h / 2) - (LOGICAL_HEIGHT / 2);

	if (cameraRect.x < 0)
	{
		cameraRect.x = 0;
	}
	if (cameraRect.x > LEVEL_WIDTH - cameraRect.w)
	{
		cameraRect.x = LEVEL_WIDTH - cameraRect.w;
	}
	if (cameraRect.y < 0)
	{
		cameraRect.y = 0;
	}
	if (cameraRect.y > LEVEL_HEIGHT - cameraRect.h)
	{
		cameraRect.y = LEVEL_HEIGHT - cameraRect.h;
	}
}