#include "StateMachine.h"

#include "ExitState.h"
#include "MenuState.h"
#include "Level1.h"
#include <iostream>

StateMachine::StateMachine()
{
	g_currentState = MenuState::Get();
	g_currentState->Enter();
}

void StateMachine::setNextState(IGameState* newState)
{
	if (newState != ExitState::Get())
	{
		g_nextState = newState;
	}
}

void StateMachine::changeState()
{
	if (g_nextState != nullptr)
	{
		g_currentState->Exit();
		g_nextState->Enter();

		g_currentState = g_nextState;
		g_nextState = nullptr;
	}
}

void StateMachine::HandleEvent(SDL_Event& event)
{
	g_currentState->HandleEvent(event);
}

void StateMachine::Update()
{
	g_currentState->Update();
}

void StateMachine::Render()
{
	g_currentState->Render();
}
