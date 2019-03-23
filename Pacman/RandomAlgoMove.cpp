/**
  *************************************************************************************************************************
  * @file    PacLife.cpp
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   Random move algorithm
  **************************************************************************************************************************
*/
/*includes*/
#include"RandomAlgoMove.h"
#include"MovableObjects.h"
#include"Map.h"
#include"Help.h"
#include<algorithm>

/**
* @brief constructor
* @param1 map pointer
* @param2 pacman pointer
*/
RandomAlgoMove::RandomAlgoMove(std::shared_ptr<Map> _map, MovableObjects* _obj) :
	map(_map),
	obj(_obj)
{
	moves.reserve(4);
}

/**
* @brief get random move
* @note
* @param1 current position
* @param2 move velocity
* @retval new move
*/
Move RandomAlgoMove::get_move(SDL_Point, int vel)
{
	velocity = vel;
	/*random move*/
	return RandomMove();
}

/**
* @brief get random move
* @note
* @retval new move
*/
Move RandomAlgoMove::RandomMove()
{
	/*move in chosen direction*/
	if (moves_qty > 0)
	{
		--moves_qty;
		SDL_Point p = make_move();
		/*move if direction is valid*/
		if (isValid(p))
		{
			move.pos = p;
			return move;
		}
	}

	/*find valid direction */
	FindMove();

	move.pos = make_move();

	return move;
}

/**
* @brief find new random move
* @note
* @retval
*/
void RandomAlgoMove::FindMove()
{
	SDL_Point src = obj->get_pos();
	SDL_Point pos;
	Direction dir;
	/*clear possible moves*/
	moves.clear();
	/*find possible directions*/
	for (int i = 0; i < 4; ++i)
	{
		pos = src;
		switch(i)
		{
		case 0:
			pos.x -= velocity;
			dir = Direction::LEFT;
			break;
		case 1:
			pos.x += velocity;
			dir = Direction::RIGHT;
			break;
		case 2:
			pos.y -= velocity;
			dir = Direction::UP;
			break;
		case 3:
			pos.y += velocity;
			dir = Direction::DOWN;
			break;
		}
		if (isValid(pos))
		{
			moves.push_back(dir);
		}
	}
	/*randomize number of moves*/
	Rand_int rand_qty(DefaultValues::MinRandomMoves, DefaultValues::MaxRandomMoves);

	if (moves_qty == 0)
		moves_qty = rand_qty();

	/*choose direction*/
	if (moves.size() > 1)
	{
		std::vector<Direction>::iterator it = std::find(moves.begin(), moves.end(), prev_dir);
		if (it != moves.end())
			moves.erase(it);

		Rand_int rand(0, static_cast<unsigned>(moves.size() - 1));
		prev_dir = move.direction = moves[rand()];
	}
	else if (moves.empty())
	{
		move.direction = Direction::NONE;
	}
	else
	{
		prev_dir = Direction::NONE;
		move.direction = *moves.begin();
	}
}

/**
* @brief get new position from direction
* @note
* @retval new position
*/
SDL_Point RandomAlgoMove::make_move()
{
	SDL_Point src = obj->get_pos();
	switch (move.direction)
	{
	case Direction::DOWN:
		src.y += velocity;
		break;
	case Direction::UP:
		src.y -= velocity;
		break;
	case Direction::RIGHT:
		src.x += velocity;
		break;
	case Direction::LEFT:
		src.x -= velocity;
		break;
	case Direction::NONE:
		break;
	}
	/*check limits*/
	switch (map->limits_check(src))
	{
	case LimitsCheck::LEFT:
		src.x = (DefaultValues::MapWidthInPixels + DefaultValues::MapShiftX) - DefaultValues::TileWidth / 2;
		break;
	case LimitsCheck::RIGHT:
		src.x = DefaultValues::MapShiftX + DefaultValues::TileWidth / 2;
		break;
	default:
		break;
	}
	return src;
}

/**
* @brief check if new position is valid
* @note
* @param1 new position
* @retval true if position is valid
*/
bool RandomAlgoMove::isValid(SDL_Point pos)
{
	SDL_Rect rect = obj->get_rect(); 
	rect.x = pos.x; rect.y = pos.y;
	return !map->check_wall_collision(rect);
}