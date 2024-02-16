#pragma once

#include "IObject.h"
#include "Texture.h"

class Font : public IObject
{
public:
	Font();
	~Font();
	void Render(SDL_Rect camera);
	void Render();
	void SetX(int x);
	void SetY(int y);
	SDL_Rect GetRect();
	std::size_t GetTextSize() const { return text.size(); }
public:
	void operator=(const char* temp);
	void SetSymbol(const char temp);

private:
	SDL_Rect rect{};
	SDL_Rect srcrect{};
	Texture* texture{ nullptr };
	std::string text{};
	const int textSize{ 32 };
};

