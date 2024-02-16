#include "DialogBox.h"

#include "globals.h"
#include "constants.h"
#include <iostream>

DialogBox::DialogBox()
{
	font = new Font{};
	font->SetX(120);
	font->SetY(450);

	texture = new Texture{};
	texture->LoadTexture("assets/dialogBox.png");

	textureRect = { 15, 410, 1250, 300 };
}

DialogBox::~DialogBox()
{
	delete texture;
	delete font;
}

void DialogBox::Update()
{
	if ((changeTextTime + 60) < SDL_GetTicks())
	{
		renderText.clear();
		for (std::size_t i{0}; i < text.size(); ++i)
		{
			if(i < showCharacters)
			{
				renderText += text[i];
			}
		}
		changeTextTime = SDL_GetTicks();

		if (showCharacters >= text.size())
		{
			showCharacters = text.size();
		}
		else
		{
			++showCharacters;
		}

		*font = renderText.c_str();
	}
}

void DialogBox::Render()
{

	texture->Render(nullptr, &textureRect);

	font->Render();
}

void DialogBox::ChangeText(const char* _text)
{
	text = _text;

	showCharacters = 0;
	renderText.clear();
}
