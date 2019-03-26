/**
  *************************************************************************************************************************
  * @file    Tile.h
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    17-March-2019
  * @brief   Tile class
  **************************************************************************************************************************
*/
#ifndef TILE_H
#define TILE_H
/*includes*/
#include<SDL.h>
#include"DefaultValues.h"
/*Predeclared  classes*/
class cmp_tile_x;

class Tile
{
	friend class cmp_tile_x;
public:
	/*Constructor*/
	Tile() = default;

	/**
	* @brief constructor
	* @param1 position x
	* @param2 position y
	* @param3 type
	*/
	Tile(int x, int y, int tiletype) :tyle_type(tiletype) {
		box.w = DefaultValues::TileWidth;
		box.h = DefaultValues::TileHeight;
		box.x = x;
		box.y = y;
	};

	/**
	* @brief constructor
	* @param1 position x
	* @param2 position y
	* @param3 width
	* @param4 height
	* @param5 type
	*/
	Tile(int x, int y,int w,int h ,int tiletype) :tyle_type(tiletype) {
		box.w = w;
		box.h = h;
		box.x = x;
		box.y = y;
	};

	/**
	* @brief get state
	* @note
	* @retval tile type
	*/
	int get_type() {return tyle_type;};

	/**
	* @brief get tile rectangle
	* @note
	* @retval tile rectangle
	*/
	SDL_Rect get_rect() const {return box;} 

private:
	SDL_Rect box;
	int tyle_type;
};



#endif
