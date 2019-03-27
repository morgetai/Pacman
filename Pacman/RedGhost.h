/**
  *************************************************************************************************************************
  * @file    RedGhost.h
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   RedGhost class
  **************************************************************************************************************************
*/
#ifndef GHOST_H
#define GHOST_H
/*includes*/
#include<memory>
#include<SDL.h>
#include<array>
#include<vector>
#include"Help.h"
#include"GhostBase.h"
#include"MovableObjects.h"

/*Predeclared  classes*/
class SmartAlgoMove;
class RandomAlgoMove;
class Animation;
class Map;
class Image;
struct Move;
enum class Direction;



class RedGhost:public GhostBase
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
	* @param7 eaten point
	* @param8 pacman pointer
	* @param9 maze
	* @param10 map pointer
	* @param11 renderer pointer
	*/
	RedGhost(std::string, std::string, std::string, std::string,
		SDL_Rect, SDL_Point, SDL_Point,
		std::shared_ptr<MovableObjects>,
		std::vector<int>, std::shared_ptr<Map>, std::shared_ptr<SDL_Renderer>);
	/*Destructor*/
	virtual ~RedGhost();

	/**
	* @brief setting ghost state
	* @note
	* @param1 new state
	* @retval
	*/
	void set_state(GhostState) override;

	/**
	* @brief render ghost
	* @retval none
	*/
	void render() override;

	/**
	* @brief move ghost
	* @note
	* @retval returns new ghost rectangle
	*/
	SDL_Rect move() override;

	/**
	* @brief returns ghost state
	* @note
	* @retval ghjost state
	*/
	GhostState get_state() const override;

	/**
	* @brief returns ghost to a start point
	* @note
	* @retval
	*/
	void reset() override;

	/**/
private:

	/**
	* @brief move in all states except eaten
	* @note
	* @param1 new move
	* @retval
	*/
	void move_base(Move);

	/**
	* @brief move in eaten state
	* @note
	* @param1 new move
	* @retval
	*/
	void move_eaten(Move);
	/**/
	std::array<std::unique_ptr<Animation>, 4> NormalAnimation;
	std::array<std::unique_ptr<Image>, 4> EatenImg;
	std::unique_ptr<Animation> FrightenedAnim;
	std::unique_ptr<Animation> FrightenedAnimEnd;
	/**/
	SDL_Point ScatterPoint;
	SDL_Point EatenPoint;
	SDL_Point StartPoint;
	SDL_Rect EatenRect;
	/**/
	std::shared_ptr<MovableObjects> Pacman;
	/**/
	const std::unique_ptr<SmartAlgoMove> SmartAlgo;
	const std::unique_ptr<RandomAlgoMove> RandomAlgo;
	/**/
	GhostState state;
	GhostState prev_state;
	/**/
	Direction direction;
	Uint32 StartFrTime;//start time of frightened
};

#endif