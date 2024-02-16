#pragma once
#include <bitset>

#include "IObject.h"
#include "Tile.h"
#include "GameObject.h"
#include "Font.h"

namespace Engine
{
	enum ImGuiFlags
	{
		PLACE_BLOCK,
		//SHOW_GRID,

		MAX_FLAGS
	};

	class ImGuiLayer
	{
	public:
		void Update(SDL_Rect camera, std::vector<Tile*>& tiles, std::vector<GameObject*>& gameobjects, Font* font = nullptr);
		void Render(SDL_Rect camera);
		
		bool isEditor();
	private:
		void toggleEditor();
		void PlaceObject(SDL_Rect camera);

	private:
		IObject* object{ nullptr };
		//Tile* tile{ nullptr };
		//GameObject* gameobject{ nullptr };

		bool showGrid{ false };
		bool showMouseHitbox{ false };
		std::bitset<2> flags;
	};
}