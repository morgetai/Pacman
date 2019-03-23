/**
  *************************************************************************************************************************
  * @file    InteractiveObjEngine.h
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    15-March-2019
  * @brief   Controls dots and fruits objects
  **************************************************************************************************************************
*/
#ifndef INTERACTIVEOBJECTSENGINE_H
#define INTERACTIVEOBJECTSENGINE_H
/*includes*/
#include<memory>
#include<SDL.h>
#include<vector>
/*Predeclared  classes*/
class Fruit;
class PacDots;
class Dot;

enum class ObjectCollisonType
{
	NONE_COLLISION,
	DOT_EATEN,
	BIG_DOT_EATEN,
	FRUIT_EATEN,
	ALL_DOTS_EATEN
};

class InteractiveObjEngine
{
public:
	/**
	* @brief constructor
	* @param1 dots vector
	* @param2 renderer pointer
	*/
	InteractiveObjEngine(std::vector<Dot>, std::shared_ptr<SDL_Renderer>);
	/*Destructor*/
	~InteractiveObjEngine();

	/**
	* @brief check collision with dots and fruits
	* @note
	* @param1 pacman rectangle
	* @retval ObjectCollisonType
	*/
	ObjectCollisonType CheckCollision(SDL_Rect);

	/**
	* @brief render all interactive objects
	* @note
	* @retval
	*/
	void render();

	/**
	* @brief run engine
	* @note
	* @retval
	*/
	void run();

	/**
	* @brief reset dots and fruit
	* @note
	* @retval
	*/
	void reset();
private:
	/**/
	std::unique_ptr<PacDots> Dots;
	std::unique_ptr<Fruit> Fruits;
	size_t dotscnt;//number of eaten dots
	Uint32 start_msecond;//start time
	bool ActiveFtuit;//activate fruit
	bool firstfruit;//generate first fruit
	bool secondfruit;//generate second fruit
};

#endif
