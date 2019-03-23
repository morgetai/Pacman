/**
  *************************************************************************************************************************
  * @file    Dot.h
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    13-March-2019
  * @brief   Dot class
  **************************************************************************************************************************
*/


#ifndef DOT_H
#define DOT_H

/*includes*/
#include<SDL.h>
#include"DefaultValues.h"
/*Predeclared  classes*/
class PacDots;
class cmp_dot_x;


class Dot
{
public:
	/**
	* @brief constructor
	* @param1 position x
	* @param2 position y
	*/
	Dot(int x, int y) 
	{ rect.x = x; rect.y = y;
	rect.w = DefaultValues::DotWeight; rect.h = DefaultValues::DotHeight; }

	/**
	* @brief returns rectangle of the current dot
	* @note  
	* @retval rectangle
	*/
	SDL_Rect get_rect() const { return rect; }

	/**
	* @brief returns coordinates of the current dot
	* @note
	* @retval rectangle
	*/
	SDL_Point get_pos() const { SDL_Point p; p.x = rect.x; p.y = rect.y; return p; }

private:

	/*friend classes*/
	friend class PacDots;
	friend class cmp_dot_x;

	/**
	* @brief sets current dot as big dot
	* @note
	* @retval none
	*/
	void set_big_dot() 
	{
		rect.x -= DefaultValues::DotWeight /2; rect.y -= DefaultValues::DotHeight /2;
		rect.w = DefaultValues::BigDotWeight; rect.h = DefaultValues::BigDotHeight;
	};

	/**
	* @brief discards current dot of being big
	* @note
	* @retval none
	*/
	void discard_big_dot()
	{
		rect.x += DefaultValues::DotWeight / 2; rect.y += DefaultValues::DotHeight / 2;
		rect.w = DefaultValues::DotWeight; rect.h = DefaultValues::DotHeight;
	}

	SDL_Rect rect;//dot rectangle
};

/*functor for dots comparison*/
class cmp_dot_x
{
public:
	bool operator() (const Dot& t, int i) const { return t.rect.x < i; }
	bool operator() (int i, const Dot& t) const { return i < t.rect.x; }
};

#endif
