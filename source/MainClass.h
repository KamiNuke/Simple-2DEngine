#pragma once
#include <SDL.h>	
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Window.h"
#include "Texture.h"
#include "StateMachine.h"

class MainClass
{
public:

	MainClass();
	~MainClass();

	void Loop();
	void Update();
	void Render();

private:
	StateMachine* state{ nullptr };
	Window* window{ nullptr };
};

