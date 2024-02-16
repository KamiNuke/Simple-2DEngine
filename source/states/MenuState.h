#pragma once

#include "IGameState.h"

#include "Texture.h"
#include "Font.h"

class MenuState : public IGameState
{
public:
	static MenuState* Get();

	void Enter();
	void Exit();

	void HandleEvent(SDL_Event& event);
	void Update();
	void Render();

private:
	Texture backgroundTex;
	Font* text{ nullptr };

private:
	static MenuState s_MenuState;

	~MenuState() {}
};



