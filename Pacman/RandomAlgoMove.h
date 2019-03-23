/**
  *************************************************************************************************************************
  * @file    PacLife.h
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   Random move algorithm
  **************************************************************************************************************************
*/

#ifndef RANDOMALGOMOVE_H
#define RANDOMALGOMOVE_H
/*includes*/
#include"MoveAlgorithmBase.h"
#include"GhostBase.h"
#include"DefaultValues.h"
#include<vector>
#include<memory>

/*Predeclared  classes*/
class MovableObjects;
class Map;
struct Move;

class RandomAlgoMove:public MoveAlgorithmBase
{
public:
	/**
	* @brief constructor
	* @param1 map pointer
	* @param2 pacman pointer
	*/
	RandomAlgoMove(std::shared_ptr<Map>, MovableObjects*);
	/*Destructor*/
	virtual ~RandomAlgoMove() { ; };

	/**
	* @brief get random move
	* @note
	* @param1 current position
	* @param2 move velocity
	* @retval new move
	*/
	virtual Move get_move(SDL_Point, int vel = DefaultValues::GhostVelocity);
protected:
	/**
	* @brief check if new position is valid
	* @note
	* @param1 new position
	* @retval true if position is valid
	*/
	bool isValid(SDL_Point);

	/**
	* @brief get random move
	* @note
	* @retval new move
	*/
	Move RandomMove();
	MovableObjects* obj;//pacman pointer
	int moves_qty;//number of random moves
	Direction prev_dir;
private:

	/**
	* @brief find new random move
	* @note
	* @retval
	*/
	void FindMove();

	/**
	* @brief get new position from direction
	* @note
	* @retval new position
	*/
	SDL_Point make_move();

	std::shared_ptr<Map> map;
	std::vector<Direction> moves;//possible directions
	Move move;//current move
};
#endif // !RANDOMALGOMOVE_H
