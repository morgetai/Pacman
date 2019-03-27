/**
  *************************************************************************************************************************
  * @file    DummyAlgoMove.h
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    13-March-2019
  * @brief   Move algorithm for dummy ghosts
  **************************************************************************************************************************
*/

#ifndef DUMMYALGOMOVE_H
#define DUMMYALGOMOVE_H

/*includes*/
#include"RandomAlgoMove.h"
#include"DefaultValues.h"
#include<memory>

/*Predeclared  classes*/
class MovableObjects;
class Map;

class DummyAlgoMove:public RandomAlgoMove
{
public:
	/**
	* @brief constructor
	* @param1 pointer to a map
	* @param2 pointer to a pacman
	*/
	DummyAlgoMove(std::shared_ptr<Map>, MovableObjects*);

	/*Destructor*/
	virtual ~DummyAlgoMove() { ; };

	/**
	* @brief get current move from algorithm
	* @param1 current point
	* @param2 velocity
	* @note
	* @retval current move
	*/
	Move get_move(SDL_Point, int vel = DefaultValues::GhostVelocity) override;
private:

	/**
	* @brief finding a short path from surrent position to a pacman
	* @param1 current point
	* @note
	* @retval true if path was found
	*/
	bool ShortDir(SDL_Point);

	/**
	* @brief finding random move
	* @note
	* @retval none
	*/
	void RandomDir();

	/**
	* @brief calculating distance between two points
	* @param1,2 points
	* @note
	* @retval distance
	*/
	float CalcDistance(SDL_Point, SDL_Point);
private:
	Move move;//current move
};

#endif // !DUMMYALGOMOVE_H

