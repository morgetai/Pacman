/**
  *************************************************************************************************************************
  * @file    MovableObjects.cpp
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   Base class for movable objects
  **************************************************************************************************************************
*/
/*includes*/
#include"MovableObjects.h"
#include"Map.h"

/**
* @brief constructor
* @param1 start rectangle
*/
MovableObjects::MovableObjects(SDL_Rect _rect)
{
	rect.w = _rect.w; rect.h = _rect.h;
	rect.x = _rect.x; rect.y = _rect.y;
}

/**
* @brief set object position
* @note
* @param1 new rectangle
* @retval
*/
void MovableObjects::set_pos(SDL_Point p)
{ 
	rect.x = p.x;
	rect.y = p.y;
};

/**
* @brief get position
* @note
* @retval returns current position
*/
SDL_Point MovableObjects::get_pos()
{
	SDL_Point ret;
	ret.x = rect.x;
	ret.y = rect.y;
	return ret;
}

/**
* @brief get rectangle
* @note
* @retval returns current rectangle
*/
SDL_Rect MovableObjects::get_rect() const
{
	return rect;
}