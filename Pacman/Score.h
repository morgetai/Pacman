/**
  *************************************************************************************************************************
  * @file    Score.h
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    17-March-2019
  * @brief   Game score
  **************************************************************************************************************************
*/
#ifndef SCORE_H
#define SCORE_H
/*includes*/
#include<memory>
#include<SDL.h>
#include<string>

/*Predeclared  classes*/
class Font;
class Image;
enum class ObjectCollisonType;
enum class GHOST_COLLISION;
class MovableObjects;

class Score
{
public:
	/**
	* @brief constructor
	* @param1 x position
	* @param2 y position
	* @param3 renderer pointer
	* @param4 path to ttf file
	*/
	Score(int ,int ,std::shared_ptr<SDL_Renderer> ,std::string  );

	/**
	* @brief render score
	* @retval none
	*/
	void render();

	/**
	* @brief increment score with dot or fruit
	* @note
	* @param1 ObjectCollisonType
	* @retval score
	*/
	Score& operator+=(ObjectCollisonType);

	/**
	* @brief increment score with ghost
	* @note
	* @param1 GHOST_COLLISION
	* @retval score
	*/
	Score& operator+=(GHOST_COLLISION);

	/**
	* @brief reset
	* @note set score to zero
	* @retval 
	*/
	void reset();


private:
	unsigned long long score;//current score
	size_t ghost_multiplier;//multiplier for eaten ghosts
	std::unique_ptr<Font> text;
	std::unique_ptr<Font> score_text;//current score text
};


#endif
