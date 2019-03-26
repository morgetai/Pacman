/**
  *************************************************************************************************************************
  * @file    Map.h
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   Map class
  **************************************************************************************************************************
*/
#ifndef MAP_H
#define MAP_H
/*includes*/
#include<memory>
#include<vector>
#include<algorithm>
#include"Tile.h"

/*Predeclared  classes*/
class Sprite;

enum class LimitsCheck
{
	LEFT,
	RIGHT,
	NONE
};

class Map
{
public:
	/**
	* @brief constructor
	* @param1 Tiles
	* @param2 Renderer
	*/
	Map(std::vector<Tile>, std::shared_ptr<SDL_Renderer>);
	/*Destructor*/
	~Map();

	/**
	* @brief check collision with walls
	* @note
	* @param1 movable object rectangle
	* @retval true if collision
	*/
	bool check_wall_collision(SDL_Rect rect);

	/**
	* @brief check if object is out of map ranges
	* @note 
	* @param1 movable object rectangle
	* @retval LimitsCheck
	*/
	LimitsCheck limits_check(SDL_Point);

	/**
	* @brief render all tiles
	* @note
	* @retval
	*/
	void render();

private:
	typedef std::vector<std::pair<int, uint16_t>> TilesQty;
	typedef std::vector<Tile> Tiles;
	typedef std::vector<Tile>::iterator TilesIt;
	Tiles tiles;
	TilesQty tiles_qty;//number of different types of tiles
	std::unique_ptr<Sprite> map_sprite_20x20;
	std::unique_ptr<Sprite> map_sprite_20x40;
	std::unique_ptr<Sprite> map_sprite_40x20;
	std::unique_ptr<Sprite> map_sprite_40x40;
	int xLimitLeft;
	int xLimitRight;

};





#endif

