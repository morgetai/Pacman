/**
  *************************************************************************************************************************
  * @file    MovableObjects.h
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   Base class for movable objects
  **************************************************************************************************************************
*/
#ifndef MOVABLEOBJECTS_H
#define MOVABLEOBJECTS_H
/*includes*/
#include<SDL.h>
#include<memory>

class MovableObjects
{
public:
	/*Destructor*/
	virtual ~MovableObjects() { ; };

	/**
	* @brief render object
	* @note
	* @retval
	*/
	virtual void render() = 0;

	/**
	* @brief move object
	* @note
	* @retval new position
	*/
	virtual SDL_Rect move() = 0;

	/**
	* @brief get position
	* @note
	* @retval returns current position
	*/
	SDL_Point get_pos();

	/**
	* @brief get rectangle
	* @note
	* @retval returns current rectangle
	*/
	SDL_Rect get_rect() const;
protected:
	/**
	* @brief set object position
	* @note
	* @param1 new rectangle
	* @retval 
	*/
	void set_pos(SDL_Point);

	/**
	* @brief constructor
	* @param1 start rectangle
	*/
	MovableObjects(SDL_Rect _rect);
private:
	SDL_Rect rect;
};

#endif
