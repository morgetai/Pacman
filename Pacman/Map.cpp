/**
  *************************************************************************************************************************
  * @file    Map.cpp
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   Map class
  **************************************************************************************************************************
*/
/*includes*/
#include"Map.h"
#include"Game_State.h"
#include"File_Reader.h"
#include"Primitives.h"
#include"Help.h"
#include"DefaultValues.h"
#include<utility>
#include <numeric>
#include <iostream>

/**
* @brief constructor
* @param1 Tiles
* @param2 Renderer
*/
Map::Map(std::vector<Tile> _tiles, std::shared_ptr<SDL_Renderer> r):
	tiles(std::move(_tiles)),
	map_sprite_20x20(std::make_unique<Sprite>(22,r, DefaultValues::Tile20x20Path)),
	map_sprite_20x40(std::make_unique<Sprite>(5, r, DefaultValues::Tile20x40Path)),
	map_sprite_40x20(std::make_unique<Sprite>(5, r, DefaultValues::Tile40x20Path)),
	map_sprite_40x40(std::make_unique<Sprite>(8, r, DefaultValues::Tile40x40Path))
{
	xLimitLeft = DefaultValues::MapShiftX - DefaultValues::TileWidth;
	xLimitRight = DefaultValues::MapWidthInPixels + (DefaultValues::TileWidth/2) + DefaultValues::MapShiftX;
	//x sort
	std::sort(tiles.begin(), tiles.end(), [this](const Tile& a, const Tile& b) 
	{
		return a.get_rect().x < b.get_rect().x;	
	});

	uint16_t accumulate = 0;

	//y sort
	for (int x = DefaultValues::MapShiftX; x <= DefaultValues::MapWidthInPixels + DefaultValues::MapShiftX; )
	{

		std::pair<Tiles::iterator, Tiles::iterator> range = 
			std::equal_range(tiles.begin(), tiles.end(), x, cmp_rect_x<Tile>());
		//
		if (range.first != range.second)
		{
			tiles_qty.push_back(std::make_pair(x, accumulate));

			//sorting y
			std::sort(range.first, range.second, [this](Tile& a, Tile& b)
			{
				return a.get_rect().y < b.get_rect().y;
			});

			//accumulating quantity
			accumulate += static_cast<uint16_t>(range.second - range.first);
		}
		x += DefaultValues::TileWidth;
	}	
}
/*Destructor*/
Map::~Map()
{
	;
}

/**
* @brief render all tiles
* @note
* @retval
*/
void Map::render()
{
	int type;
	for (std::vector<Tile>::iterator it = tiles.begin(); it != tiles.end(); ++it)
	{
		type = it->get_type();
		if (type < 22)
		{
			map_sprite_20x20->set_rect(it->get_rect());
			map_sprite_20x20->render(type);
		}
		else if (type >= 22 && type < 27)
		{
			map_sprite_20x40->set_rect(it->get_rect());
			map_sprite_20x40->render(type%22);
		}
		else if (type >= 27 && type < 32)
		{
			map_sprite_40x20->set_rect(it->get_rect());
			map_sprite_40x20->render(type%27);
		}
		else
		{
			map_sprite_40x40->set_rect(it->get_rect());
			map_sprite_40x40->render(type%32);
		}
	}
}

/**
* @brief check collision with walls
* @note
* @param1 movable object rectangle
* @retval true if there is collision
*/
bool Map::check_wall_collision(SDL_Rect obj)
{
	//finding the upper bound for the current movable object position
	TilesQty::iterator upper =
		std::upper_bound(tiles_qty.begin(), tiles_qty.end(), obj.x + DefaultValues::TileWidth, []
		(int x, std::pair<int, int> rhs) -> bool
	{
		return rhs.first > x;
	});

	TilesQty::iterator lower =
		std::lower_bound(tiles_qty.begin(), tiles_qty.end(), obj.x - DefaultValues::TileWidth * 2, []
		(std::pair<int, int> rhs, int x) -> bool
	{
		return rhs.first < x;
	});

	//setting high
	TilesIt check_high;
	if (upper == tiles_qty.end())
		check_high = tiles.end()-1;
	else
		check_high = tiles.begin() + upper->second;
	//setting low 
	TilesIt check_low = tiles.begin() + lower->second;

	//Collission
	for (; check_low <= check_high; ++check_low)
	{
		if (SDL_HasIntersection(&obj, &check_low->get_rect()))
			return true;
	}
	return false;
}

/**
* @brief check if object is out of map ranges
* @note
* @param1 movable object rectangle
* @retval LimitsCheck
*/
LimitsCheck Map::limits_check(SDL_Point obj)
{
	if (obj.x <= xLimitLeft)
		return LimitsCheck::LEFT;
	else if (obj.x >= xLimitRight)
		return LimitsCheck::RIGHT;
	return LimitsCheck::NONE;
}