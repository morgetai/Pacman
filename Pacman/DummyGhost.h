/**
  *************************************************************************************************************************
  * @file    DummyGhost.h
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    13-March-2019
  * @brief   Dummy ghost class
  **************************************************************************************************************************
*/


#ifndef DUMMY_GHOST_H
#define DUMMY_GHOST_H
/*includes*/
#include<SDL.h>
#include<memory>
#include<array>
#include<string>
#include<vector>
#include"GhostBase.h"
/*Predeclared  classes*/
class Animation;
class Image;
class SmartAlgoMove;
class RandomAlgoMove;
class DummyAlgoMove;
class MovableObjects;
class MoveAlgorithmBase;
class Map;
struct Move;
enum class Direction;


class DummyGhost:public GhostBase
{
public:
	/**
	* @brief constructor
	* @param1 path to normal animation file
	* @param2 path to eaten animation file
	* @param3 path to frightened animation file
	* @param4 path to second frightened animation file
	* @param5 start rectangle
	* @param6 scatter point
	* @param7 point near ghost house
	* @param8 pacman pointer
	* @param9 maze
	* @param9 map pointer
	* @param10 renderer pointer
	*/
	DummyGhost(std::string, std::string, std::string, std::string, SDL_Rect, SDL_Point, SDL_Point,
		std::shared_ptr<MovableObjects>, std::vector<int>, std::shared_ptr<Map> , std::shared_ptr<SDL_Renderer>);
	/*Destructor*/
	virtual ~DummyGhost();

	/**
	* @brief setting ghost state
	* @param1 new state
	* @note
	* @retval 
	*/
	virtual void set_state(GhostState);

	/**
	* @brief returns ghost state
	* @note
	* @retval ghjost state
	*/
	virtual GhostState get_state();

	/**
	* @brief render ghost
	* @retval none
	*/
	virtual void render();

	/**
	* @brief move ghost
	* @note
	* @retval returns new ghost rectangle
	*/
	virtual SDL_Rect move();

	/**
	* @brief returns ghost to a start point
	* @note
	* @retval
	*/
	virtual void reset();
private:
	/**
	* @brief moving in chase state
	* @note
	* @retval none
	*/
	void move_chase();

	/**
	* @brief moving in scatter state
	* @note
	* @retval none
	*/
	void move_scatter();

	/**
	* @brief moving in frightened state
	* @note
	* @retval none
	*/
	void move_frightened();

	/**
	* @brief moving in eaten state
	* @note
	* @retval none
	*/
	void move_eaten();

	/**
	* @brief getting from ghost house
	* @param1 reference to a current move algorithm
	* @note
	* @retval move
	*/
	Move move_from_home(std::unique_ptr<MoveAlgorithmBase>&, SDL_Point);
	/*private variable*/
	std::array<std::unique_ptr<Animation>, 4> NormalAnimation;//array of normal animation
	std::array<std::unique_ptr<Image>, 4> EatenImg;//array of eaten animation 
	std::unique_ptr<Animation> FrightenedAnim;//pointer to a frightened animation
	std::unique_ptr<Animation> FrightenedAnimEnd;//pointer to a second frightened animation

	std::unique_ptr<MoveAlgorithmBase> SmartAlgo;//smart move algorithm
	std::unique_ptr<MoveAlgorithmBase> DummyAlgo;//dummy move algorithm
	std::unique_ptr<MoveAlgorithmBase> RandomAlgo;//random move algorithm

	std::shared_ptr<MovableObjects> Pacman;//pointer to the pacman

	SDL_Point ScatterPoint;//scatter point 
	SDL_Point EatenPoint;//eaten point(same as start position)
	SDL_Point GetFromHousePoint;//point near ghost house
	SDL_Rect GetFromHouseRect;//rectangle
	SDL_Rect EatenRect;//rectangle

	GhostState state;//current state
	GhostState prev_state;//previous state
	Direction direction;//current direction

	Uint32 StartFrTime;//frightened state start time
	bool GetFromHouse;//true if getting from house needed
};

#endif
