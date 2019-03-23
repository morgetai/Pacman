/**
  *************************************************************************************************************************
  * @file    GhostBase.h
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    14-March-2019
  * @brief   Ghosts base class
  **************************************************************************************************************************
*/
#ifndef GHOST_BASE_H
#define GHOST_BASE_H
/*includes*/
#include"MovableObjects.h"


enum class GhostState
{
	CHASE,
	SCATTER,
	FRIGHTENED,
	EATEN
};

class GhostBase:public MovableObjects
{
public:
	/**
	* @brief constructor
	* @param1 Start rectangle
	*/
	GhostBase(SDL_Rect _rect) :MovableObjects(_rect) {}
	/*Destructor*/
	virtual ~GhostBase() { ; };

	/**
	* @brief set new state
	* @note
	* @param1 new state
	* @retval 
	*/
	virtual void set_state(GhostState) = 0;

	/**
	* @brief get current state
	* @note
	* @retval
	*/
	virtual GhostState get_state() = 0;

	/**
	* @brief render a ghost
	* @note
	* @retval
	*/
	virtual void render() = 0;

	/**
	* @brief move ghost
	* @note
	* @retval new ghost rectangle
	*/
	virtual SDL_Rect move() = 0;

	/**
	* @brief return ghost to a start position
	* @note
	* @retval
	*/
	virtual void reset() = 0;
};


#endif
