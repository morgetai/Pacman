/**
  *************************************************************************************************************************
  * @file    Help.cpp
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    15-March-2019
  * @brief   Some support classes and functions
  **************************************************************************************************************************
*/
/*includes*/
#include"Help.h"
#include"Tile.h"
#include"Map.h"
#include"DefaultValues.h"

/**
* @brief turns tile to SDL_point
* @note x and y of left cornet of a tile
* @param1 tile number
* @retval SDL_Point
*/
SDL_Point TileToSDL_Point(int tile)
{
	SDL_Point tilep;
	tilep.x = ((tile - ((tile / DefaultValues::MapWidthInTiles) * DefaultValues::MapWidthInTiles))*
		DefaultValues::TileWidth + DefaultValues::MapShiftX) ;
	tilep.y = (((tile / DefaultValues::MapWidthInTiles)*DefaultValues::TileHeight) + DefaultValues::MapShiftY) ;
	return tilep;
}

/**
* @brief turns SDL_Point to tile
* @note
* @param1 SDL_Point
* @retval tile number
*/
int SDL_PointToTile(SDL_Point pos)
{
	return ((pos.x - DefaultValues::MapShiftX + DefaultValues::TileWidth / 2) / DefaultValues::TileWidth
		+ ((pos.y - DefaultValues::MapShiftY + DefaultValues::TileHeight / 2) 
			/ DefaultValues::TileHeight) * DefaultValues::MapWidthInTiles);

}

/**
* @brief checks if delay time elapsed
* @note
* @param1 delay
* @param1 start time
* @retval true if delay time elapsed
*/
bool TimeElapsed(Uint32 delay, Uint32 start_msecond)
{
	if (delay == 0) return false;
	Uint32 current_msecond = SDL_GetTicks();

	if ((current_msecond - start_msecond) >= delay)
		return true;
	else return false;
}