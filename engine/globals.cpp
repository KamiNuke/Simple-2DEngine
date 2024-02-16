#include "globals.h"

SDL_Renderer* g_renderer{ nullptr };
int SCREEN_WIDTH{ 1280 };
int SCREEN_HEIGHT{ 720 };

IGameState* g_currentState{ nullptr };
IGameState* g_nextState{ nullptr };

bool isHitbox{ false };