/**
  *************************************************************************************************************************
  * @file    Fruit.cpp
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    14-March-2019
  * @brief   Fruit object
  **************************************************************************************************************************
*/
/*includes*/
#include"Fruit.h"
#include"Help.h"
#include"Primitives.h"

/**
* @brief constructor
* @param1 map position
* @param2 position where last eaten fruit is shown
* @param3 path to a fruit sprite
* @param4 pointer to a renderer
*/
Fruit::Fruit(SDL_Rect mappos, SDL_Rect showeaten, std::string path, std::shared_ptr<SDL_Renderer> r):
	Images(std::make_unique<Sprite>(
		4,//number of images in fruit sprite
		r,
		path)),
	map_rect(mappos),
	show_rect(showeaten)
{
	/*don't show eaten fruit*/
	EatenImg = -1;
}

/*Destructor*/
Fruit::~Fruit()
{
	;
}

/**
* @brief checks collision with current fruit
* @note
* @param1 pacman rectangle
* @retval true if fruit was eaten
*/
bool Fruit::check_collision(SDL_Rect obj)
{
	if (active)
	{
		if (SDL_HasIntersection(&obj, &map_rect))
		{
			active = false;
			EatenImg = CurrentImg;
			return true;
		}
	}
	return false;
}

/**
* @brief generate fruit
* @note
* @retval
*/
void Fruit::GenerateFruit()
{
	active = true;
	Rand_int rand(0, 3);
	CurrentImg = rand();
}

/**
* @brief kills current fruit
* @note
* @retval
*/
void Fruit::KillFruit()
{
	active = false;
}

/**
* @brief render
* @note
* @retval
*/
void Fruit::render()
{
	if (active)
	{
		Images->set_rect(map_rect);
		Images->render(CurrentImg);
	}
	if (EatenImg > 0)
	{
		Images->set_rect(show_rect);
		Images->render(EatenImg);
	}
}

/**
* @brief reset fruits
* @note
* @retval
*/
void Fruit::reset()
{
	active = false;
	EatenImg = -1;
}


