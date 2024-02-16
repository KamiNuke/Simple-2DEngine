#pragma once
#include <SDL.h>

//Abstract class/interface for all game states in the game
class IGameState
{
public:
	virtual void Enter() = 0;
	virtual void Exit() = 0;

	virtual void HandleEvent(SDL_Event& event) = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	~IGameState() {};
};

