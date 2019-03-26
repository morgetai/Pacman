/**
  *************************************************************************************************************************
  * @file    DummyAlgoMove.cpp
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    13-March-2019
  * @brief   Move algorithm for dummy ghosts
  **************************************************************************************************************************
*/
/*includes*/
#include"DummyAlgoMove.h"
#include<math.h>
#include<vector>
#include"MovableObjects.h"
#include"Map.h"
#include"Help.h"
#include"RandomAlgoMove.h"

/**
* @brief constructor
* @param1 pointer to a map
* @param2 pointer to a pacman
*/
DummyAlgoMove::DummyAlgoMove(std::shared_ptr<Map> _map, MovableObjects* _obj) :
	RandomAlgoMove(_map,_obj)
{}

/**
* @brief get current move from algorithm
* @param1 current point
* @param2 velocity
* @note
* @retval current move
*/
Move DummyAlgoMove::get_move(SDL_Point dest, int vel)
{
	velocity = vel;
	/*if there's short path*/
	if (ShortDir(dest))
	{
		RandomAlgoMove::prev_dir = Direction::NONE;
	}
	/*if there's no short path*/
	else
	{
		RandomDir();
	}
	return move;
}

/**
* @brief finding a short path from surrent position to a pacman
* @param1 current point
* @note
* @retval true if path was found
*/
bool DummyAlgoMove::ShortDir(SDL_Point dest)
{

	SDL_Point src = obj->get_pos();//current pacman position
	float dist = CalcDistance(src, dest);//distance
	bool ret = false;

	/*reached pacman*/
	if (dist < 5)
	{
		move.direction = Direction::NONE;
		return true;
	}
	/*finding short path*/
	if (RandomAlgoMove::moves_qty == 0)
	{
		Direction dir;
		SDL_Point pos;
		float dist_tmp;
		for (int i = 0; i < 4; ++i)
		{
			pos = src;
			switch (i)
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
				dist_tmp = CalcDistance(pos, dest);
				/*if distance is shorter then previous*/
				if (dist_tmp < dist)
				{
					move.direction = dir; move.pos = pos;
					ret = true;
				}
			}
		}
	}
	return ret;
}

/**
* @brief finding random move
* @note
* @retval none
*/
void DummyAlgoMove::RandomDir()
{
	move = RandomMove();
}

/**
* @brief calculating distance between two points
* @param1,2 points
* @note
* @retval distance
*/
float DummyAlgoMove::CalcDistance(SDL_Point a, SDL_Point b)
{
	return static_cast<float>(sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}
