#pragma once
#include <SDL.h>
#include <string>

class Window
{
public:
	Window(std::string_view _title);
	~Window();

	void CreateWindow();
	void ChangeWindowSize(int width, int height);
	void ChangeTitle(std::string _title);
	void ToggleFullscreen();

	SDL_Window* GetWindow() const { return window; }

private:
	SDL_Window* window{ nullptr };
	std::string title{};
	unsigned int posX{ SDL_WINDOWPOS_UNDEFINED }, posY{ SDL_WINDOWPOS_UNDEFINED };

	bool isFullscreen{ false };
};

