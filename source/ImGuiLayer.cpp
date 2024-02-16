#include "ImGuiLayer.h"
#include "globals.h"
#include "LevelFunctions.h"

#include "imgui.h"
#include <iostream>

namespace Engine
{
	void ImGuiLayer::Update(SDL_Rect camera, std::vector<Tile*>& tiles, std::vector<GameObject*>& gameobjects, Font* font)
	{
		ImGui::Begin("testWindow");
		ImGui::Text("So-called map editor");

		//Get tile and if it was taken already 
		if (ImGui::Button("Toggle Dirt"))
		{
			if (!flags[PLACE_BLOCK])
			{
				toggleEditor();

				object = new Tile{ "assets/tiles/Dirt.png", static_cast<int>(ImGui::GetMousePos().x), static_cast<int>(ImGui::GetMousePos().y), TileType::BREAKABLE };
				tiles.emplace_back(dynamic_cast<Tile*>(object));
			}
		}
		else if (ImGui::Button("Toggle Stone"))
		{
			if (!flags[PLACE_BLOCK])
			{
				toggleEditor();

				object = new Tile{ "assets/tiles/Stone.png", static_cast<int>(ImGui::GetMousePos().x), static_cast<int>(ImGui::GetMousePos().y), TileType::BREAKABLE };
				tiles.emplace_back(dynamic_cast<Tile*>(object));
			}
		}
		else if (ImGui::Button("Toggle Water_first"))
		{
			if (!flags[PLACE_BLOCK])
			{
				toggleEditor();

				object = new Tile{ "assets/tiles/Water.png", static_cast<int>(ImGui::GetMousePos().x), static_cast<int>(ImGui::GetMousePos().y), TileType::UNBREAKABLE, 5 };
				tiles.emplace_back(dynamic_cast<Tile*>(object));
			}
		}
		else if (ImGui::Button("Toggle Wine glass"))
		{
			if (!flags[PLACE_BLOCK])
			{
				toggleEditor();

				object = new GameObject{ "assets/objects/BearGlass.png", 
					static_cast<int>(ImGui::GetMousePos().x), static_cast<int>(ImGui::GetMousePos().y), 
					16, 16, 8 };
				gameobjects.emplace_back(dynamic_cast<GameObject*>(object));
			}
		}

		//Place or take object
		if (ImGui::IsMouseClicked(0))
		{
			//Place object
			if (flags[PLACE_BLOCK])
			{
				PlaceObject(camera);
			}
			//Take object
			else
			{
				SDL_Rect mouseRect{ (static_cast<int>(ImGui::GetMousePos().x) - 5) + camera.x, (static_cast<int>(ImGui::GetMousePos().y) - 5) + camera.y, 20, 20 };

				for (auto& e : tiles)
				{
					if (CheckCollision(mouseRect, e->GetRect()))
					{
						object = e;
						flags.set(PLACE_BLOCK);
						break;
					}
				}

				for (auto& e : gameobjects)
				{
					if (CheckCollision(mouseRect, e->GetRect()))
					{
						object = e;
						flags.set(PLACE_BLOCK);
						break;
					}
				}

				if (font != nullptr)
				{
					SDL_Rect tempFontRect = font->GetRect();
					tempFontRect.w = 16 * font->GetTextSize();
					if (CheckCollision(mouseRect, tempFontRect))
					{
						object = font;
						flags.set(PLACE_BLOCK);
					}
				}
			}
		}
		else if (ImGui::IsMouseClicked(1))
		{
			if (flags[PLACE_BLOCK])
			{
				PlaceObject(camera);
			}

			SDL_Rect mouseRect{ static_cast<int>(ImGui::GetMousePos().x) + camera.x, static_cast<int>(ImGui::GetMousePos().y) + camera.y, 20, 20 };

			for (int i{ 0 }; i < tiles.size(); ++i)
			{
				if (CheckCollision(mouseRect, tiles[i]->GetRect()))
				{
					delete tiles[i];
					tiles.erase(tiles.begin() + i);
					break;
				}
			}

			for (int i{ 0 }; i < gameobjects.size(); ++i)
			{
				if (CheckCollision(mouseRect, gameobjects[i]->GetRect()))
				{
					delete gameobjects[i];
					gameobjects.erase(gameobjects.begin() + i);
					break;
				}
			}
		}

		//Checkboxes
		ImGui::Checkbox("Show Grid", &showGrid);
		ImGui::Checkbox("Show Hitboxes", &isHitbox);
		ImGui::Checkbox("Show Mouse Hitbox", &showMouseHitbox);

		ImGui::End();
	}

	void ImGuiLayer::Render(SDL_Rect camera)
	{
		//Place block
		if (flags[PLACE_BLOCK])
		{
			object->SetX((static_cast<int>(ImGui::GetMousePos().x) - 15) + camera.x);
			object->SetY((static_cast<int>(ImGui::GetMousePos().y) - 15) + camera.y);
		}

		//Show grid if enabled
		if (showGrid)
		{
			for (int i{ 0 }; i < 4000; i += 32)
			{
				for (int j{ 0 }; j < 4000; j += 32)
				{
					SDL_Rect temp{ i - camera.x, j - camera.y, 32, 32 };
					SDL_RenderDrawRect(g_renderer, &temp);
				}
			}
		}

		//Show mouse hitbox
		if (showMouseHitbox)
		{
			SDL_Rect mouseRect{ (static_cast<int>(ImGui::GetMousePos().x) - 5), (static_cast<int>(ImGui::GetMousePos().y) - 5), 20, 20 };
			SDL_RenderDrawRect(g_renderer, &mouseRect);
		}

	}

	bool ImGuiLayer::isEditor()
	{
		return flags[PLACE_BLOCK];
	}

	void ImGuiLayer::toggleEditor()
	{
		flags.flip(PLACE_BLOCK);
	}

	void ImGuiLayer::PlaceObject(SDL_Rect camera)
	{
		object->SetX((static_cast<int>(ImGui::GetMousePos().x) - 15) + camera.x);
		object->SetY((static_cast<int>(ImGui::GetMousePos().y) - 15) + camera.y);

		object = nullptr;

		flags.flip(PLACE_BLOCK);
	}
}