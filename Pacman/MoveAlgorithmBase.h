/**
  *************************************************************************************************************************
  * @file    MoveAlgorithmBase.h
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   Base class for move algorithms
  **************************************************************************************************************************
*/
#ifndef MOVE_ALGO_BASE_H
#define MOVE_ALGO_BASE_H
/*includes*/
#include<SDL.h>
#include<utility>
#include"GhostBase.h"
#include"DefaultValues.h"

enum class Direction
{
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3,
	NONE
};

/**/
struct Move
{
	SDL_Point pos;
	Direction direction;
};

class MoveAlgorithmBase
{
public:
	/**
	* @brief get move
	* @note
	* @param1 current position
	* @param2 move velocity
	* @retval new move
	*/
	virtual Move get_move(SDL_Point,int vel = DefaultValues::GhostVelocity) = 0;
	/*Destructor*/
	virtual ~MoveAlgorithmBase() { ; };
protected:
	int velocity;
};

#endif
