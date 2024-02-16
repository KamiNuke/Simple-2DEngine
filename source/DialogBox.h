#pragma once
#include "Font.h"
#include "DialogBox.h"

/*
	DialogBox is a class that's used to create dialogBox in old style
	like in Omori/Undertale/Pokemon/Heartbound
	He-he
*/
class DialogBox
{
public:
	DialogBox();
	~DialogBox();

	void Update();
	void Render();

	void ChangeText(const char* _text);

private:
	Texture* texture{ nullptr };
	SDL_Rect textureRect{};

private:
	Uint32 changeTextTime{ SDL_GetTicks() };
	std::size_t showCharacters{};

	Font* font{ nullptr };
	std::string text, renderText;
};

