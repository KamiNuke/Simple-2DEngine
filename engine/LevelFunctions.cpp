#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

#include "LevelFunctions.h"


bool CheckCollision(const SDL_Rect A, const SDL_Rect B)
{
	int rightA{ A.x + A.w }, rightB{ B.x + B.w };
	int leftA{ A.x }, leftB{ B.x };
	int topA{ A.y }, topB{ B.y };
	int bottomA{ A.y + A.h }, bottomB{ B.y + B.h };

	if (rightA < leftB)
	{
		return false;
	}
	else if (leftA > rightB)
	{
		return false;
	}
	else if (topA > bottomB)
	{
		return false;
	}
	else if (bottomA < topB)
	{
		return false;
	}

	return true;
}

static std::ostream& operator<<(std::ostream& out, const TileType& type)
{
	switch (type)
	{
	case TileType::BREAKABLE:
		out << "BREAKABLE";
		break;
	case TileType::UNBREAKABLE:
		out << "UNBREAKABLE";
		break;
	default:
		break;
	}

	return out;
}

static std::istream& operator>>(std::istream& in, TileType& type)
{
	std::string temp{};
	in >> temp;
	if (temp == "BREAKABLE")
	{
		type = TileType::BREAKABLE;
	}
	else if (temp == "UNBREAKABLE")
	{
		type = TileType::UNBREAKABLE;
	}

	return in;
}

//You have to load Objects and Tiles at the same object and later allocate them to specific YOU KNOW
//IM FORGOR AYOOOOOOOO
void LoadLevel(std::string levelName, std::vector<Tile*>& tiles, std::vector<GameObject*>& gameobject)
{
	//check for levels in ../levels/
	std::ifstream read{ "levels/" + levelName };
	if (!read.is_open())
	{
		std::cerr << "Couldn't load level file\n";
		return;
	}
	else
	{
		std::string path{};
		int x{}, y{}, w{}, h{}, animFrames{};
		TileType type;

		bool tempSwitch{ false }; //If getline will find Objects:: then switch from tiles to them
		for(std::string line; std::getline(read, line);)
		{
			std::string trash{};
			std::istringstream ss(line);

			if (!tempSwitch)
			{
				//read path
				std::getline(ss, path, ';');

				//if there's a line Objects then we add objects
				if (path == "Objects:")
				{
					tempSwitch = true;
					continue;
				}

				std::getline(ss, trash, ':');
				ss >> animFrames;

				std::getline(ss, trash, ':');
				ss >> x;

				std::getline(ss, trash, ':');
				ss >> y;

				std::getline(ss, trash, ']');
				ss >> type;

				/*
				std::cout << "Path: " << path << ", AnimFrames: " << animFrames
					<< ", X: " << x << ", Y: " << y << ", Type: " << type << std::endl;
				*/

				tiles.emplace_back(new Tile{ path, x, y, type, animFrames });

			}
			else
			{
				//x,y
				std::getline(ss, trash, ':');
				ss >> x;
				std::getline(ss, trash, ':');
				ss >> y;
				std::getline(ss, trash, ']');

				//w,h
				std::getline(ss, trash, ':');
				ss >> w;
				std::getline(ss, trash, ':');
				ss >> h;
				std::getline(ss, trash, ':');
				ss >> animFrames;

				std::getline(ss, trash, ' ');
				std::getline(ss, trash, ';');
				gameobject.emplace_back(new GameObject{ trash, x, y, w, h, animFrames });
			}

		}

	}

	read.close();
}

void SaveLevel(std::string levelName, std::vector<Tile*>& tiles, std::vector<GameObject*>& gameobject)
{
	std::ofstream write{ "levels/" + levelName };
	if (!write.is_open())
	{
		std::cerr << "Couldn't save level file\n";
		return;
	}
	else
	{
		for (int i{ 0 }; i < tiles.size(); ++i)
		{
			write << tiles[i]->GetPath() << "; AnimFrames: "
				<< tiles[i]->GetAnimationFrames()
				<< " [x: " << tiles[i]->GetRect().x 
				<< " y: " << tiles[i]->GetRect().y << " ] " 
				<< tiles[i]->GetType() << '\n';
		}

		write << "Objects:\n";
		for (int i{ 0 }; i < gameobject.size(); ++i)
		{
			write << "[x: " << gameobject[i]->GetRect().x << " y: " << gameobject[i]->GetRect().y << " ] " <<
				"[w: " << gameobject[i]->GetRect().w << " h: " << gameobject[i]->GetRect().h << " ]"
				<< "animFrames: " << gameobject[i]->GetAnimationFrames() << ' '
				<< gameobject[i]->GetTexturePath() << ';' << '\n';
		}
	}

	write.close();
}