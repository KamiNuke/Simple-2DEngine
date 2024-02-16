#pragma once
#include <SDL.h>

#include "IGameState.h"
#include "globals.h"

class StateMachine
{
public:
	StateMachine();

	void setNextState(IGameState* newState);
	void changeState();

	void HandleEvent(SDL_Event& event);
	void Update();
	void Render();

	IGameState* GetState() const { return g_currentState; }
};

