#pragma once

#include "IGameState.h"

class ExitState : public IGameState
{
public:
	static ExitState* Get();

	void Enter();
	void Exit();

	void HandleEvent(SDL_Event& event);
	void Update();
	void Render();
private:
	static ExitState s_ExitState;

	~ExitState() {}
};

