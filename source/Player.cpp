#include "Player.h"

#include "ResourceManager.h"
#include "globals.h"
#include "LevelFunctions.h"

Player::Player(std::string path, int xPos, int yPos,
	int spriteWidth, int spriteHeight, int animationSprites)
{
	playerTexture.LoadTexture(path);

	texturePath = path;

	dstrect.x = xPos;
	dstrect.y = yPos;
	dstrect.w = spriteWidth;
	dstrect.h = spriteHeight;

	srcrect.x = 0;
	srcrect.y = 0;
	srcrect.w = spriteWidth;
	srcrect.h = spriteHeight;

	animFrames = animationSprites;
}

Player::~Player()
{
	ResourceManager::Get().UnloadTexture(texturePath);
}

void Player::HandleEvent(SDL_Event& event)
{
	//std::cout << dstrect.x << "," << dstrect.y << '\n';
}


void Player::Move(std::vector<Tile*>& tiles)
{
	isWalking = false;
	const Uint8* keyState{ SDL_GetKeyboardState(0) };

	if (keyState[SDL_SCANCODE_D] || keyState[SDL_SCANCODE_RIGHT])
	{
		dstrect.x += speed;
		flip = SDL_FLIP_NONE;
		for (const auto& e : tiles)
		{
			if (e->GetType() != TileType::BREAKABLE && CheckCollision(dstrect, e->GetRect()))
			{
				dstrect.x -= speed;
			}
		}
		isWalking = true;
	}
	if (keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_LEFT])
	{
		dstrect.x -= speed;
		flip = SDL_FLIP_HORIZONTAL;
		for (const auto& e : tiles)
		{
			if (e->GetType() != TileType::BREAKABLE && CheckCollision(dstrect, e->GetRect()))
			{
				dstrect.x += speed;
			}
		}
		isWalking = true;
	}
	if (keyState[SDL_SCANCODE_W] || keyState[SDL_SCANCODE_UP])
	{
		dstrect.y -= speed;
		for (const auto& e : tiles)
		{
			if (e->GetType() != TileType::BREAKABLE && CheckCollision(dstrect, e->GetRect()))
			{
				dstrect.y += speed;
			}
		}
		isWalking = true;
	}
	if (keyState[SDL_SCANCODE_S] || keyState[SDL_SCANCODE_DOWN])
	{
		dstrect.y += speed;
		for (const auto& e : tiles)
		{
			if (e->GetType() != TileType::BREAKABLE && CheckCollision(dstrect, e->GetRect()))
			{
				dstrect.y -= speed;
			}
		}
		isWalking = true;
	}


}

void Player::Update(std::vector<Tile*>& tiles)
{
	Move(tiles);
}

void Player::Render(SDL_Rect camera)
{
	//Create rect depending on camera
	SDL_Rect cameraRect{ dstrect.x - camera.x, dstrect.y - camera.y, dstrect.w, dstrect.h };

	if (isWalking)
	{
		playerTexture.Render(&srcrect, &cameraRect, 0, flip);

		//If passed 0.4s then play next animation
		if (animationChangeTime + 250 < SDL_GetTicks())
		{

			if (srcrect.x >= (srcrect.w * (animFrames - 1)))
			{
				srcrect.x = srcrect.w;
				
			}
			else
			{
				srcrect.x += dstrect.w;
			}
			animationChangeTime = SDL_GetTicks();
		}

	}
	else
	{
		srcrect.x = 0;
		playerTexture.Render(&srcrect, &cameraRect, 0, flip);
	}

	//Character hitbox
	if (isHitbox)
	{
		SDL_SetRenderDrawColor(g_renderer, 0, 0xFF, 0, 0xFF);
		SDL_RenderDrawRect(g_renderer, &cameraRect);
	}
}