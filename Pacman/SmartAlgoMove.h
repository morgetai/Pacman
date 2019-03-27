/**
  *************************************************************************************************************************
  * @file    SmartAlgoMove.h
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    17-March-2019
  * @brief   Smart move algorithm
  **************************************************************************************************************************
*/
#ifndef SMARTALGOMOVE_H
#define SMARTALGOMOVE_H
/*includes*/
#include"MoveAlgorithmBase.h"
#include"DefaultValues.h"
#include<vector>
/*Predeclared  classes*/
class MovableObjects;

class SmartAlgoMove:public MoveAlgorithmBase
{
public:
	/**
	* @brief constructor
	* @param1 maze
	* @param2 pacman pointer
	*/
	SmartAlgoMove(std::vector<int>, MovableObjects*);
	/*Destructor*/
	virtual ~SmartAlgoMove() { ; };

	/**
	* @brief get random move
	* @note
	* @param1 current position
	* @param2 move velocity
	* @retval new move
	*/
	Move get_move(SDL_Point, int vel = DefaultValues::GhostVelocity) override;
private:

	/**
	* @brief get next move using Lee algorithm
	* @note
	* @param1 current position
	* @retval true if move was found
	*/
	bool LeeAlgo(SDL_Point);

	/**
	* @brief check if new position is valid
	* @note
	* @param1 new position
	* @retval true if position is valid
	*/
	bool isValid(int pos);

	/**
	* @brief move to center
	* @note moves to center of a tile
	* @param1 current tile
	* @retval true if move is possible
	*/
	bool move_to_center(int);

	/**
	* @brief alignment by x
	* @note
	* @param1 current tile
	* @retval true if alignment was done
	*/
	bool alighn_by_x(int);

	/**
	* @brief alignment by y
	* @note
	* @param1 current tile
	* @retval true if alignment was done
	*/
	bool alighn_by_y(int);

	/**
	* @brief calculate source tile
	* @note
	* @param1 current position
	* @retval current tile
	*/
	int get_src_tile(SDL_Point);

	/**
	* @brief calculate source tile
	* @note
	* @param1 current position
	* @retval current tile
	*/
	void get_next_tile(int);
	/**/
	int old_src, old_dest;
	int next_tile;
	Move move;//current move
	const std::vector<int> maze;
	MovableObjects* const obj;//pacman pointer
};



#endif
