#pragma once
#include "IGameState.h"
#include "Tile.h"
#include "Player.h"
#include "constants.h"
#include "Camera.h"
#include "GameObject.h"
#include "DialogBox.h"

#include "ImGuiLayer.h"

class Level1 : public IGameState
{
public:
	static Level1* Get();

	void Enter();
	void Exit();

	void HandleEvent(SDL_Event& event);
	void Update();
	void Render();

private:
	std::vector<Tile*> tiles;
	std::vector<GameObject*> gameobjects;

	Player* player{ nullptr };
	Camera* camera{ nullptr };
	DialogBox* dialogBox{ nullptr };

private:
	Engine::ImGuiLayer gui;

	static Level1 s_Level1;

	~Level1() {}
};


