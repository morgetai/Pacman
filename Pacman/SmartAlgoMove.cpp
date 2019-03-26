/**
  *************************************************************************************************************************
  * @file    SmartAlgoMove.cpp
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    17-March-2019
  * @brief   Smart move algorithm
  **************************************************************************************************************************
*/
/*includes*/
#include"SmartAlgoMove.h"
#include"MovableObjects.h"
#include"Tile.h"
#include"Map.h"
#include"File_Reader.h"
#include"MovableObjects.h"
#include"Help.h"
#include"DefaultValues.h"
#include<queue>
#include<iostream>

/**
* @brief constructor
* @param1 maze
* @param2 pacman pointer
*/
SmartAlgoMove::SmartAlgoMove(std::vector<int> _maze, MovableObjects* _obj) :
	maze(std::move(_maze)),
	obj(_obj)
{
}

/**
* @brief get random move
* @note
* @param1 current position
* @param2 move velocity
* @retval new move
*/
Move SmartAlgoMove::get_move(SDL_Point dest, int vel)
{
	/*set velocity*/
	velocity = vel;
	/*get current position*/
	move.pos = obj->get_pos();

	if (!LeeAlgo(dest))
	{
		move.direction = Direction::NONE;
	}
	return move;
}

/**
* @brief get next move using Lee algorithm
* @note
* @param1 current position
* @retval true if move was found
*/
bool SmartAlgoMove::LeeAlgo(SDL_Point _dest)
{
	//SDL_Rect pos;
	int dpos[4] = { 1, -1, DefaultValues::MapWidthInTiles,-DefaultValues::MapWidthInTiles };

	int src = get_src_tile(obj->get_pos());

	int dest = ((_dest.x - DefaultValues::MapShiftX + DefaultValues::TileWidth / 2) / DefaultValues::TileWidth
		+ ((_dest.y - DefaultValues::MapShiftY + DefaultValues::TileHeight / 2) / DefaultValues::TileHeight)
		* DefaultValues::MapWidthInTiles);

	/*if reached dest*/
	if (src == dest)
	{
		return false;
	}

	/*id dest not changed*/
	if (src == old_src && dest == old_dest)
	{
		goto Return;
	}

	/*main part*/
	{
		std::vector<int> grid(maze);

		// Create a queue for BFS
		std::queue<int> q;
		q.push(src);
		grid[src] = 0;

		while (!q.empty())
		{
			int curr = q.front();
			if (curr == dest)
				break;

			q.pop();

			for (int i = 0; i < 4; ++i)
			{
				int pos = curr + dpos[i];
				if (isValid(pos) && grid[pos] == DefaultValues::MazeCorridor)
				{
					grid[pos] = grid[curr] + 1;
					q.push(pos);
				}
			}
		}

		/*dest is unattainable*/
		if (grid[dest] == DefaultValues::MazeCorridor) return false;

		//path recovery
		int len = grid[dest];
		int curr_pos = dest;

		while (len > 0)
		{
			--len;
			for (int i = 0; i < 4; ++i)
			{
				int pos = curr_pos + dpos[i];
				if (isValid(pos) && grid[pos] == len)
				{
					curr_pos = pos;
					if (len == 0)
					{
						switch (i)
						{
						case 0:
							move.direction = Direction::LEFT;
							break;
						case 1:
							move.direction = Direction::RIGHT;
							break;
						case 2:
							move.direction = Direction::UP;
							break;
						case 3:
							move.direction = Direction::DOWN;
							break;
						}
					}
				}
			}
		}
	}


Return:
	/*moveing to the center of a current tile*/
	if (!move_to_center(src))
	{
		/*if the center of a tile is achieved make a move*/
		switch (move.direction)
		{
		case Direction::LEFT:
			move.pos.x -= velocity;
			break;
		case Direction::RIGHT:
			move.pos.x += velocity;
			break;
		case Direction::UP:
			move.pos.y -= velocity;
			break;
		case Direction::DOWN:
			move.pos.y += velocity;
			break;
		}
	}

	/*set next tile*/
	get_next_tile(src);

	return true;
}

/**
* @brief move to center
* @note moves to center of a tile
* @param1 current tile
* @retval true if move is possible
*/
bool SmartAlgoMove::move_to_center(int pos)
{
	switch (move.direction)
	{
	case Direction::UP:
		pos -= DefaultValues::MapWidthInTiles;
		return alighn_by_x(pos);
	case Direction::DOWN:
		pos += DefaultValues::MapWidthInTiles;
		return alighn_by_x(pos);
	case Direction::LEFT:
		return alighn_by_y(--pos);
	case Direction::RIGHT:
		return alighn_by_y(++pos);
	}
	return false;
}

/**
* @brief alignment by y
* @note
* @param1 current tile
* @retval true if alignment was done
*/
bool SmartAlgoMove::alighn_by_y(int pos)
{
	bool ret = false;
	int tileY = TileToSDL_Point(pos).y;
	int objY = obj->get_pos().y;

	/*above the center of a tile*/
	if (objY > tileY)
	{
		move.direction = Direction::UP;
		objY = objY - velocity;

		if (objY < tileY)	move.pos.y = tileY;
		else move.pos.y = objY;
		ret = true;
	}

	/*below the center of a tile*/
	else if (objY < tileY)
	{
		move.direction = Direction::DOWN;
		objY = objY + velocity;
		if (objY > tileY) move.pos.y = tileY;
		else move.pos.y = objY;
		ret = true;
	}
	return ret;
}

/**
* @brief alignment by x
* @note
* @param1 current tile
* @retval true if alignment was done
*/
bool SmartAlgoMove::alighn_by_x(int pos)
{
	bool ret = false;
	int tileX = TileToSDL_Point(pos).x;
	int objX = obj->get_pos().x;

	/**/
	if (objX > tileX)
	{
		move.direction = Direction::LEFT;
		objX = objX - velocity;
		if (objX < tileX)
			move.pos.x = tileX;
		else move.pos.x = objX;
		ret = true;
	}

	/**/
	else if (objX < tileX)
	{
		move.direction = Direction::RIGHT;
		objX = objX + velocity;
		if (objX > tileX)
			move.pos.x = tileX;
		else move.pos.x = objX;
		ret = true;
	}
	return ret;
}


/**
* @brief calculate source tile
* @note
* @param1 current position
* @retval current tile
*/
int SmartAlgoMove::get_src_tile(SDL_Point pos)
{

	int tile = SDL_PointToTile(pos);
	/*calculating rectangle which is located at the center of a current tile*/
	SDL_Point p = TileToSDL_Point(tile);

	SDL_Rect tilerect;
	tilerect.x = p.x;
	tilerect.y = p.y;
	tilerect.w = 2;
	tilerect.h = 2;

	//return current tile if located at his center
	if (SDL_PointInRect(&pos, &tilerect))
	{
		old_src = tile;
		return tile;
	}

	//return previous tile
	else
	{
		if (tile != old_src && tile != next_tile)
			old_src = tile;
		return old_src;
	}
}

/**
* @brief calculate source tile
* @note
* @param1 current position
* @retval current tile
*/
void SmartAlgoMove::get_next_tile(int src)
{
	switch (move.direction)
	{
	case Direction::UP:
		src -= DefaultValues::MapWidthInTiles;
		break;
	case Direction::DOWN:
		src += DefaultValues::MapWidthInTiles;
		break;
	case Direction::LEFT:
		--src;
		break;
	case Direction::RIGHT:
		++src;
		break;
	}
	if (next_tile != src)
	{
		next_tile = src;
	}
}

/**
* @brief check if new position is valid
* @note
* @param1 new position
* @retval true if position is valid
*/
bool SmartAlgoMove::isValid(int pos)
{
	// return true if row number and column number 
	// is in range 
	return (pos >= 0 && pos < (DefaultValues::MapWidthInTiles*DefaultValues::MapHeightInTiles)
		&& maze[pos] == DefaultValues::MazeCorridor);
}


