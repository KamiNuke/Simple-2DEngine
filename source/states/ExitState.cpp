#include "ExitState.h"

ExitState ExitState::s_ExitState;

ExitState* ExitState::Get()
{
	return &s_ExitState;
}

void ExitState::Enter()
{
}

void ExitState::Exit()
{
}

void ExitState::HandleEvent(SDL_Event& event)
{
}

void ExitState::Update()
{
}

void ExitState::Render()
{
}
