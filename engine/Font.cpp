#include "Font.h"

#include "ResourceManager.h"
#include "globals.h"
#include "LevelFunctions.h"

Font::Font()
{
	texture = new Texture{};
	texture->LoadTexture("assets/fontWHITE.png");

	rect.x = 0;
	rect.y = 0;
	rect.w = textSize;
	rect.h = textSize;

	srcrect.x = 0;
	srcrect.y = 0;
	srcrect.w = 16;
	srcrect.h = 16;
}

Font::~Font()
{
	delete texture;
}

void Font::Render(SDL_Rect camera)
{
	SDL_Rect renderRect{ rect.x - camera.x, rect.y - camera.y, rect.w, rect.h };
	for (const auto& e : text)
	{
		//If text not in camera then we do not render it
		if (CheckCollision(camera, rect))
		{
			//If there's a space then do not render it
			if (e != ' ')
			{
				//Set Symbol position aka get symbol
				SetSymbol(e);

				texture->Render(&srcrect, &renderRect);

				if (isHitbox)
				{
					SDL_RenderDrawRect(g_renderer, &renderRect);
				}
			}

			//In order to not overlap letters we need to move new letters
			renderRect.x += textSize;
		}			
	}
	
}

void Font::Render()
{
	SDL_Rect tempRect{ rect.x, rect.y, rect.w, rect.h };
	for (const auto& e : text)
	{
		if (e != ' ')
		{
			//Set Symbol position aka get symbol
			SetSymbol(e);

			texture->Render(&srcrect, &tempRect);
		}

		//In order to not overlap letters we need to move new letters
		tempRect.x += textSize;

		if (tempRect.x > 1200)
		{
			tempRect.x = 64;
			tempRect.y += 64;
		}
	}
}

void Font::SetX(int x)
{
	rect.x = x;
}

void Font::SetY(int y)
{
	rect.y = y;
}

SDL_Rect Font::GetRect()
{
	return rect;
}

void Font::operator=(const char* temp)
{
	text = temp;
}

void Font::SetSymbol(const char temp)
{
	switch (temp)
	{
	case 'A':
	case 'a':
		srcrect.x = 0;
		srcrect.y = 0;
		break;
	case 'B':
	case 'b':
		srcrect.x = 16;
		srcrect.y = 0;
		break;
	case 'C':
	case 'c':
		srcrect.x = 32;
		srcrect.y = 0;
		break;
	case 'D':
	case 'd':
		srcrect.x = 48;
		srcrect.y = 0;
		break;
	case 'E':
	case 'e':
		srcrect.x = 64;
		srcrect.y = 0;
		break;
	case 'F':
	case 'f':
		srcrect.x = 80;
		srcrect.y = 0;
		break;
	case 'G':
	case 'g':
		srcrect.x = 0;
		srcrect.y = 16;
		break;
	case 'H':
	case 'h':
		srcrect.x = 16;
		srcrect.y = 16;
		break;
	case 'I':
	case 'i':
		srcrect.x = 32;
		srcrect.y = 16;
		break;
	case 'J':
	case 'j':
		srcrect.x = 48;
		srcrect.y = 16;
		break;
	case 'K':
	case 'k':
		srcrect.x = 64;
		srcrect.y = 16;
		break;
	case 'L':
	case 'l':
		srcrect.x = 80;
		srcrect.y = 16;
		break;
	case 'M':
	case 'm':
		srcrect.x = 0;
		srcrect.y = 32;
		break;
	case 'N':
	case 'n':
		srcrect.x = 16;
		srcrect.y = 32;
		break;
	case 'O':
	case 'o':
		srcrect.x = 32;
		srcrect.y = 32;
		break;
	case 'P':
	case 'p':
		srcrect.x = 48;
		srcrect.y = 32;
		break;
	case 'Q':
	case 'q':
		srcrect.x = 64;
		srcrect.y = 32;
		break;
	case 'R':
	case 'r':
		srcrect.x = 80;
		srcrect.y = 32;
		break;
	case 'S':
	case 's':
		srcrect.x = 0;
		srcrect.y = 48;
		break;
	case 'T':
	case 't':
		srcrect.x = 16;
		srcrect.y = 48;
		break;
	case 'U':
	case 'u':
		srcrect.x = 32;
		srcrect.y = 48;
		break;
	case 'V':
	case 'v':
		srcrect.x = 48;
		srcrect.y = 48;
		break;
	case 'W':
	case 'w':
		srcrect.x = 64;
		srcrect.y = 48;
		break;
	case 'X':
	case 'x':
		srcrect.x = 80;
		srcrect.y = 48;
		break;
	case 'Y':
	case 'y':
		srcrect.x = 0;
		srcrect.y = 64;
		break;
	case 'Z':
	case 'z':
		srcrect.x = 16;
		srcrect.y = 64;
		break;
	case '0':
		srcrect.x = 32;
		srcrect.y = 64;
		break;
	case '1':
		srcrect.x = 48;
		srcrect.y = 64;
		break;
	case '2':
		srcrect.x = 64;
		srcrect.y = 64;
		break;
	case '3':
		srcrect.x = 80;
		srcrect.y = 64;
		break;
	case '4':
		srcrect.x = 0;
		srcrect.y = 80;
		break;
	case '5':
		srcrect.x = 16;
		srcrect.y = 80;
		break;
	case '6':
		srcrect.x = 32;
		srcrect.y = 80;
		break;
	case '7':
		srcrect.x = 48;
		srcrect.y = 80;
		break;
	case '8':
		srcrect.x = 64;
		srcrect.y = 80;
		break;
	case '9':
		srcrect.x = 80;
		srcrect.y = 80;
		break;
	default:
		break;
	}
}
