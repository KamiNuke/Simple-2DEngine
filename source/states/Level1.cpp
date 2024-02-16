#include "Level1.h"
#include <iostream>

#include "MenuState.h"

#include "LevelFunctions.h"
#include "globals.h"
#include "ResourceManager.h"

Level1 Level1::s_Level1;
Level1* Level1::Get()
{
	return &s_Level1;
}

void Level1::Enter()
{
	//REMEMBER YOUR LEVEL SHOULD BE BIGGER THAN YOUR SCREEN RESOLUTION
	//OR YOU'LL BROKE EVERYTHING
	constexpr int LEVEL_WIDHT{ 2000 };
	constexpr int LEVEL_HEIGHT{ 2000 };
	camera = new Camera{ LEVEL_WIDHT, LEVEL_HEIGHT };

	//set vector's size to 50
	tiles.reserve(LEVEL_WIDHT + LEVEL_HEIGHT);
	gameobjects.reserve((LEVEL_WIDHT + LEVEL_HEIGHT) / 2);


	//Load level after entering the state
	//RELEASE AND DEBUG FEATURE
	LoadLevel("level1", tiles, gameobjects);

	//Create player
	player = new Player{ "assets/characters/player/LongswordMan.png", 
		0, 0, 32, 32, 8 };

	dialogBox = new DialogBox{};
	dialogBox->ChangeText("Hello new player PRESS E to remove this message");
}

void Level1::Exit()
{
	//Save lever after leaving the state
	//DEBUG ONLY
	SaveLevel("level1", tiles, gameobjects);

	if (dialogBox != nullptr)
	{
		delete dialogBox;
		dialogBox = nullptr;
	}

	if (camera != nullptr)
	{
		delete camera;
		camera = nullptr;
	}

	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}
	
	//delete gameobjects
	for (std::size_t i{ 0 }; i < gameobjects.size(); ++i)
	{
		delete gameobjects[i];
	}
	//clear gameobjects vector
	gameobjects.clear();

	//delete tiles
	for (std::size_t i{ 0 }; i < tiles.size(); ++i)
	{
		delete tiles[i];
	}
	//clear tile vector
	tiles.clear();

	//Clear all loaded textures
	ResourceManager::Destruct();
}

void Level1::HandleEvent(SDL_Event& event)
{
	//Change scale of camera
	player->HandleEvent(event);

	if (event.key.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE && event.key.repeat == 0)
	{
		g_nextState = MenuState::Get();
	}

	//
	if (event.key.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_E && event.key.repeat == 0)
	{
		delete dialogBox;
		dialogBox = nullptr;
	}
}

void Level1::Update()
{
	player->Update(tiles);

	//Update camera based on player position
	camera->Update(player->GetRect());

	//Update dialog box if it exists
	if (dialogBox != nullptr)
	{
		dialogBox->Update();
	}
	
	//ImGui update
	gui.Update(camera->GetRect(), tiles, gameobjects);
}

void Level1::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 0, 0xFF, 0, 0xFF);

	//Render tiles
	for (std::size_t i{ 0 }; i < tiles.size(); ++i)
	{
		tiles[i]->Render(camera->GetRect());
	}

	//Render tiles
	for (std::size_t i{ 0 }; i < gameobjects.size(); ++i)
	{
		gameobjects[i]->Render(camera->GetRect());
	}

	player->Render(camera->GetRect());

	//Render dialog box if it exists
	if (dialogBox != nullptr)
	{
		dialogBox->Render();
	}

	//ImGui update
	gui.Render(camera->GetRect());
}
