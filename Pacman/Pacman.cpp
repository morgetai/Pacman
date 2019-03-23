/**
  *************************************************************************************************************************
  * @file    Pacman.cpp
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   Pacman class
  **************************************************************************************************************************
*/
/*includes*/
#include"Pacman.h"
#include"Animation.h"
#include"Tile.h"
#include"Primitives.h"
#include"Map.h"
#include"MoveAlgorithmBase.h"
#include"Help.h"
#include"PacmanLife.h"
#include"File_Reader.h"
#include"DefaultValues.h"
#include <sstream>
#include<utility>
#include<cmath>

/**
* @brief constructor
* @param1 start rectangle
* @param2 renderer pointer
* @param3 map pointer
* @param4 maze
* @param5 normal animation path
* @param6 dead animation path
*/
Pacman::Pacman(SDL_Rect rect,std::shared_ptr<SDL_Renderer> r, std::shared_ptr<Map> _map,std::vector<int> maze,
	std::string path,std::string death_image_path):
	MovableObjects(rect),
	map(_map),
	Life (std::make_unique<PacmanLife>(DefaultValues::PacLifeImg,r)),
	Maze(maze)
{

	/**/
	StartPos.x = rect.x; StartPos.y = rect.y;
	/*normal state animation*/
	std::istringstream ss(path);
	std::string str;
	size_t index = 0;
	while (!ss.eof())
	{
		std::getline(ss, str,' ');
		animation[index++] = std::make_unique<Animation>(DefaultValues::TileWidth, DefaultValues::TileHeight,
			3, //number of sprites
			SpriteOrientation::HORIZONTAL,
			r, 
			str);
	}
	/*dead state animation*/
	animation[index] = std::make_unique<Animation>(DefaultValues::TileWidth, DefaultValues::TileHeight,
		11, //number of sprites
		SpriteOrientation::HORIZONTAL,
		r,
		death_image_path);
}

/**
* @brief render pacman
* @note
* @retval
*/
void Pacman::render()
{
	switch (state)
	{
	case PacmanState::STATE_OK:
		animation[static_cast<int>(direction)]->setpos(get_pos());
		animation[static_cast<int>(direction)]->render();
		break;
	case PacmanState::STATE_DEAD:
		animation[static_cast<int>(PacmanState::STATE_DEAD)]->setpos(get_pos());
		animation[static_cast<int>(PacmanState::STATE_DEAD)]->render();
		break;
	}
	Life->render();
}

/**
* @brief set pacman state
* @note
* @param1 new pacman state
* @retval
*/
void Pacman::set_state(PacmanState newstate)
{
	state = newstate;
}

/**
* @brief set new direction
* @note
* @param1 new direction
* @retval
*/
void Pacman::set_direction(Direction dir)
{
	direction = dir;
}

/**
* @brief move object
* @note
* @retval new position
*/
SDL_Rect Pacman::move()
{
	SDL_Rect old_rec = get_rect();
	SDL_Rect new_rec = get_rect();
	SDL_Point p;
	switch (direction)
	{
	case Direction::UP:
		new_rec.y -= DefaultValues::PacmanVelocity;
		break;
	case Direction::DOWN:
		new_rec.y += DefaultValues::PacmanVelocity;
		break;
	case Direction::LEFT:
		new_rec.x -= DefaultValues::PacmanVelocity;
		break;
	case Direction::RIGHT:
		new_rec.x += DefaultValues::PacmanVelocity;
		break;
	}

	/*change direction*/
	if (DirectionChanged())
	{
		if (Alignment(new_rec))
		{
			p.x = new_rec.x; p.y = new_rec.y;
			goto LIMITS;
		}
		else goto CHECK;
	}
	else 
	{
		/*check wall collision*/
		CHECK:if (map->check_wall_collision(new_rec))
		{
			p.x = old_rec.x; p.y = old_rec.y;
		}
		else
		{
			p.x = new_rec.x; p.y = new_rec.y;
		}
	}

	/*check limits*/
	LIMITS:switch (map->limits_check(p))
	{
	case LimitsCheck::LEFT:
		p.x = (DefaultValues::MapWidthInPixels + DefaultValues::MapShiftX) - DefaultValues::TileWidth / 2;
		break;
	case LimitsCheck::RIGHT:
		p.x = DefaultValues::MapShiftX + DefaultValues::TileWidth / 2;
		break;
	default:
		break;
	}
	Prevdirection = direction;
	/*set new position*/
	set_pos(p);
	return get_rect();
}

/**
* @brief check direction change
* @note
* @retval true if direction changed
*/
bool Pacman::DirectionChanged()
{
	bool ret = false;
	switch (direction)
	{
	case Direction::UP:
		if (Direction::LEFT == Prevdirection ||
			Direction::RIGHT == Prevdirection)
			ret = true;
		break;
	case Direction::DOWN:
		if (Direction::LEFT == Prevdirection ||
			Direction::RIGHT == Prevdirection)
			ret = true;
		break;
	case Direction::LEFT:
		if (Direction::UP == Prevdirection ||
			Direction::DOWN == Prevdirection)
			ret = true;
		break;
	case Direction::RIGHT:
		if (Direction::UP == Prevdirection ||
			Direction::DOWN == Prevdirection)
			ret = true;
		break;
	default :
		ret = false;
	}
	return ret;
}

/**
* @brief alignment by x and y
* @note
* @param1 new position
* @retval true if alignment was done
*/
bool Pacman::Alignment(SDL_Rect& NewRect)
{
	int Tiledest;
	SDL_Point p; 
	p.x = NewRect.x; p.y = NewRect.y;
	int SourceTile = SDL_PointToTile(p);
	switch (direction)
	{
		case Direction::UP:
			Tiledest = SourceTile - DefaultValues::MapWidthInTiles;
			break;
		case Direction::DOWN:
			Tiledest = SourceTile + DefaultValues::MapWidthInTiles;
			break;
		case Direction::LEFT:
			Tiledest = SourceTile - 1;
			break;
		case Direction::RIGHT:
			Tiledest = SourceTile + 1;
			break;
	}
	/*if dest tile is not a wall*/
	if (Maze[Tiledest] == DefaultValues::MazeCorridor)
	{
		switch (direction)
		{
		case  Direction::UP:
			if (AlignByX(Tiledest, p))
			{
				NewRect.x = p.x;
				return true;
			}
			break;
		case Direction::DOWN:
			if (AlignByX(Tiledest, p))
			{
				NewRect.x = p.x;
				return true;
			}
			break;
		case Direction::LEFT:
			if (AlignByY(Tiledest, p))
			{
				NewRect.y = p.y;
				return true;
			}
			break;
		case Direction::RIGHT:
			if (AlignByY(Tiledest, p))
			{
				NewRect.y = p.y;
				return true;
			}
			break;
		}
	}
	else
	{
		return false;
	}
	return false;
}

/**
* @brief alignment by x
* @note
* @param1 tile
* @param2 new position
* @retval true if alignment was done
*/
bool Pacman::AlignByX(int dest, SDL_Point& SrcP)
{
	int destX = TileToSDL_Point(dest).x;
	int SrcX = SrcP.x;
	if (std::abs(destX - SrcX) < 8)
	{
		SrcP.x = destX;
		return true;
	}
	else return false;
}

/**
* @brief alignment by y
* @note
* @param1 tile
* @param2 new position
* @retval true if alignment was done
*/
bool Pacman::AlignByY(int dest, SDL_Point& SrcP)
{
	bool ret = false;
	int destY = TileToSDL_Point(dest).y;
	int SrcY = SrcP.y;
	switch (Prevdirection)
	{
	case Direction::UP:
		if (std::abs(destY - SrcY) < 10)
		{
			ret = true;
			SrcP.y = destY;
		}
		break;
	case Direction::DOWN:
		if (std::abs(destY - SrcY) < 10)
		{
			ret = true;
			SrcP.y = destY;
		}
		break;
	}
	return ret;
}

/**
* @brief reset pacman
* @note return pacman to a start position
* @retval
*/
void Pacman::reset()
{
	state = PacmanState::STATE_OK;
	set_pos(StartPos);
}

/**
* @brief constructor
* @param1 pointer to paclife object
*/
Pacman::PacLife::PacLife(std::unique_ptr<PacmanLife>&& paclife) :
	life(std::move(paclife))
{}


