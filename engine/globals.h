#pragma once
#include <SDL.h>

#include "IGameState.h"

extern SDL_Renderer* g_renderer;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern IGameState* g_currentState;
extern IGameState* g_nextState;

extern bool isHitbox;