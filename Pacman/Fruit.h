/**
  *************************************************************************************************************************
  * @file    Fruit.h
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    14-March-2019
  * @brief   Fruit object
  **************************************************************************************************************************
*/
#ifndef FRUIT_H
#define FRUIT_H
/*includes*/
#include<vector>
#include<array>
#include<memory>
#include<SDL.h>
#include<string>
/*Predeclared  classes*/
class Sprite;

class Fruit 
{
public:
	/**
	* @brief constructor
	* @param1 map position
	* @param2 position where last eaten fruit is shown
	* @param3 path to a fruit sprite
	* @param4 pointer to a renderer
	*/
	Fruit(SDL_Rect, SDL_Rect, std::string, std::shared_ptr<SDL_Renderer>);

	/*Destructor*/
	~Fruit();

	/**
	* @brief checks collision with current fruit
	* @note  
	* @param1 pacman rectangle
	* @retval true if fruit was eaten
	*/
	bool check_collision(SDL_Rect);

	/**
	* @brief kills current fruit
	* @note
	* @retval 
	*/
	void KillFruit();

	/**
	* @brief generate fruit 
	* @note
	* @retval
	*/
	void GenerateFruit();

	/**
	* @brief render
	* @note
	* @retval
	*/
	void render();

	/**
	* @brief reset fruits
	* @note
	* @retval
	*/
	void reset();
private:
	std::unique_ptr<Sprite> Images;//fruit sprite pointer
	SDL_Rect map_rect;//location on the map
	SDL_Rect show_rect;//place where last eaten fruit is shown 
	int CurrentImg;//current fruit image
	int EatenImg;//last eaten fruit image
	bool active;//true if fruit is active
};

#endif