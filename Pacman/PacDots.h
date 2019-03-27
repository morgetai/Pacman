/**
  *************************************************************************************************************************
  * @file    PacDots.h
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   Dots class
  **************************************************************************************************************************
*/
#ifndef PAC_DOT_H
#define PAC_DOT_H
/*includes*/
#include<vector>
#include<SDL.h>
#include<memory>
/*Predeclared  classes*/
class Image;
class Dot;
enum class ObjectCollisonType;

class PacDots 
{
public:
	/**
	* @brief constructor
	* @param1 dots
	* @param2 renderer pointer
	*/
	PacDots(std::vector<Dot>, std::shared_ptr<SDL_Renderer>);
	/*Destructor*/
	 ~PacDots() { ; };

	/**
	* @brief check collision with dots and fruits
	* @note
	* @param1 pacman rectangle
	* @retval ObjectCollisonType
	*/
	 ObjectCollisonType check_collision(SDL_Rect);

	/**
	* @brief render dots
	* @note
	* @retval
	*/
	 void render();

	 /**
	* @brief reset dots
	* @note
	* @retval
	*/
	 void reset();

	 /**
	* @brief return current number of dots
	* @note
	* @retval number of dots
	*/
	 size_t size();
private:
	typedef std::vector<Dot> Dots;
	const std::unique_ptr<Image> dot_image;
	Dots dots;
	std::vector<bool> eaten_dots;
};


#endif
