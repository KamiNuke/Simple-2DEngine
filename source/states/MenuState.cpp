#include "MenuState.h"
#include "Level1.h"

#include "constants.h"
#include "ResourceManager.h"
#include "globals.h"

MenuState MenuState::s_MenuState;

MenuState* MenuState::Get()
{
	return &s_MenuState;
}

void MenuState::Enter()
{
	text = new Font{};
	text->SetX(LOGICAL_WIDTH / 4);
	text->SetY(LOGICAL_HEIGHT / 2);
	*text = "Press Z to start";

	backgroundTex.LoadTexture("assets/background/MainMenuFirst.png");
}

void MenuState::Exit()
{
	if (text != nullptr)
	{
		delete text;
		text = nullptr;
	}

	ResourceManager::Destruct();
}

void MenuState::HandleEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_Z && event.key.repeat == 0)
	{
		g_nextState = Level1::Get();
	}
}

void MenuState::Update()
{
}

void MenuState::Render()
{
	backgroundTex.Render();

	text->Render();
}
