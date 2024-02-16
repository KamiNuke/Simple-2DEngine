#include "Window.h"
#include "constants.h"
#include "globals.h"
#include <iostream>

Window::Window(std::string_view _title)
	: title{ _title }
{
	SCREEN_WIDTH = 1280;
	SCREEN_HEIGHT = 720;
	CreateWindow();
}

Window::~Window()
{
	SDL_DestroyWindow(window);
}

void Window::CreateWindow()
{
	window = SDL_CreateWindow(title.c_str(), posX, posY, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	//Move the cursor to the center of the screen
	SDL_WarpMouseInWindow(window, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

void Window::ChangeWindowSize(int width, int height)
{
	if (width <= 0 || height <= 0)
	{
		std::cerr << "Incorrect window size\n";
		return;
	}
	
	SDL_SetWindowSize(window, width, height);

	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
}

void Window::ChangeTitle(std::string _title)
{
	title = _title;
	SDL_SetWindowTitle(window, title.c_str());
}

void Window::ToggleFullscreen()
{
	if (!isFullscreen)
	{
		//Get display resolution
		SDL_DisplayMode dm;
		SDL_GetCurrentDisplayMode(0, &dm);
		SCREEN_WIDTH = dm.w;
		SCREEN_HEIGHT = dm.h;

		/*
		//If display resolution is 1920x1080 then set renderscale 3.0f
		if (SCREEN_WIDTH == 1920 && SCREEN_HEIGHT == 1080)
		{
			//SDL_RenderSetScale(g_renderer, 1.5f, 1.5f);
		}
		//RESOLUTION 1280X1080 SHOULD BE FIXED THERE'S A BUG
		else if (SCREEN_WIDTH >= 1080 && SCREEN_WIDTH <= 1280 && SCREEN_HEIGHT >= 720 && SCREEN_HEIGHT <= 1080)
		{
			//SDL_RenderSetScale(g_renderer, 2.0f, 2.34f);
		}*/

		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		isFullscreen = true;
		
		//DEBUG
		//SDL_WarpMouseInWindow(window, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}
	else
	{
		//windowed screen set to ligcal size
		SCREEN_WIDTH = LOGICAL_WIDTH;
		SCREEN_HEIGHT = LOGICAL_HEIGHT;

		//Enable windowed mode
		SDL_SetWindowFullscreen(window, 0);
		isFullscreen = false;

		//SDL_RenderSetScale(g_renderer, 1.0f, 1.0f);

		//DEBUG
		//SDL_WarpMouseInWindow(window, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}
}
