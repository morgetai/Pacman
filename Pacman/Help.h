/**
  *************************************************************************************************************************
  * @file    Help.h
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    15-March-2019
  * @brief   Some support classes and functions
  **************************************************************************************************************************
*/
#ifndef HELP_H
#define HELP_H
/*includes*/
#include<random>
#include<functional>
#include<chrono>
#include<SDL.h>

/*class for rectangle x coordinate comparison*/
template <typename T> class cmp_rect_x
{
public:
	bool operator() (const T& t, int i) const { return t.get_rect().x < i; }
	bool operator() (int i, const T& t) const { return i < t.get_rect().x; }
};

/*Randomization*/
class Rand_int {
public:
	/**
	* @brief constructor
	* @param1 from
	* @param2 to
	*/
	Rand_int(unsigned lo, unsigned hi) : p{ lo,hi }, 
		engine(static_cast<unsigned>(time(0))){ } //store the parameters

	/**
	* @brief returns random number between low and high
	* @note
	* @retval random int number
	*/
	int operator()() const { return r(); }
private:
	std::uniform_int_distribution<>::param_type p;
	std::default_random_engine engine; //random engine
	std::function<int()> r = std::bind(std::uniform_int_distribution<>{p}, engine);//random function
};

/**
* @brief turns tile to SDL_point
* @note x and y of left cornet of a tile
* @param1 tile number
* @retval SDL_Point
*/
SDL_Point TileToSDL_Point(int);

/**
* @brief turns SDL_Point to tile
* @note 
* @param1 SDL_Point
* @retval tile number
*/
int SDL_PointToTile(SDL_Point);

/**
* @brief checks if delay time elapsed
* @note
* @param1 delay
* @param1 start time
* @retval true if delay time elapsed
*/
bool TimeElapsed(Uint32, Uint32);


#endif
