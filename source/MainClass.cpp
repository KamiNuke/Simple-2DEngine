#include <iostream>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#include "MainClass.h"
#include "globals.h"
#include "constants.h"
#include "ResourceManager.h"
#include "ExitState.h"

MainClass::MainClass()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) < 0)
	{
		std::cerr << "Couldn't initialize SDL: " << SDL_GetError() << '\n';
	}

	int flags{ IMG_INIT_PNG };
	if ((IMG_Init(flags) & flags) != flags)
	{
		std::cerr << "Couldn't initialize SDL_image: " << IMG_GetError() << '\n';
	}

	if (TTF_Init() != 0)
	{
		std::cerr << "Couldn't initialize SDL_ttf: " << TTF_GetError() << '\n';
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
	{
		std::cerr << "Couldn't initialize SDL_mixer: " << Mix_GetError() << '\n';
	}

	window = new Window{ "Lonely Swordsman" };
	g_renderer = SDL_CreateRenderer(window->GetWindow(), -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

	//Game renders with the scale 2.0f
	//SDL_RenderSetIntegerScale(g_renderer, SDL_TRUE);
	SDL_RenderSetLogicalSize(g_renderer, LOGICAL_WIDTH, LOGICAL_HEIGHT);
	//SDL_SetHint(SDL_HINT_MOUSE_RELATIVE_SCALING, "1");

	//ImGui initialization
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//ImGui initialization for SDL2 and SDL2renderer
	ImGui_ImplSDL2_InitForSDLRenderer(window->GetWindow(), g_renderer);
	ImGui_ImplSDLRenderer2_Init(g_renderer);

	

	state = new StateMachine{};
}

MainClass::~MainClass()
{
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	ResourceManager::Get().Destruct();

	delete state;

	SDL_DestroyRenderer(g_renderer);
	delete window;
}

void MainClass::Loop()
{
	SDL_Event event{};
	while (g_currentState != ExitState::Get())
	{
		while (SDL_PollEvent(&event))
		{
			//Event check for ImGui
			ImGui_ImplSDL2_ProcessEvent(&event);

			if (event.type == SDL_QUIT)
			{
				g_nextState = ExitState::Get();
				state->changeState();
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_F12 && event.key.repeat == 0)
			{
				window->ToggleFullscreen();
			}
			//Disable/enable hitboxes
			else if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_F1 && event.key.repeat == 0)
			{
				if (isHitbox)
				{
					isHitbox = false;
					//std::cout << "Hitboxes is disabled\n";
				}
				else
				{
					isHitbox = true;
					//std::cout << "Hitboxes is enabled\n";
				}
			}


			state->HandleEvent(event);
		}

		state->changeState();

		// New frame for ImGui
		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		Update();
		
		ImGui::EndFrame();
		Render();
		
	}
}

void MainClass::Update()
{
	state->Update();
}

void MainClass::Render()
{
	ImGui::Render();

	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	state->Render();

	// Needs to render ImGui IDK WHY
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
	SDL_RenderPresent(g_renderer);
}
