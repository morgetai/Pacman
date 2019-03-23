/**
  *************************************************************************************************************************
  * @file    PacLife.cpp
  * @author  Gridin Andrei
  *          abgridin@gmail.com
  * @date    16-March-2019
  * @brief   Pacman life
  **************************************************************************************************************************
*/
/*includes*/
#include "PacmanLife.h"
#include"Primitives.h"

/**
* @brief constructor
* @param1 path to image
* @param2 renderer pointer
*/
PacmanLife::PacmanLife(std::string path, std::shared_ptr <SDL_Renderer> r):

	life(3)
{
	SDL_Rect rect; rect.x = 90; rect.y = 420; rect.w = 30; rect.h = 30;
	pos.x = rect.x; pos.y = rect.y;
	LifeImg = std::make_unique<Image>(rect, r, path);
}

/*Destructor*/
PacmanLife::~PacmanLife()
{
	;
}

/**
* @brief render pacman
* @note
* @retval
*/
void PacmanLife::render()
{
	/*show life images in vertical projection*/
	for (int i = 0; i < life; ++i)
	{
		SDL_Point p(pos);
		p.y += i * 40;
		LifeImg->set_pos(p);
		LifeImg->render();
	}
}

/**
* @brief decrement operator
* @note
* @retval paclife reference
*/
PacmanLife& PacmanLife::operator--()
{
	--life;
	return *this;
}

/**
* @brief cast to bool
* @note
* @retval true if life is greater then 0
*/
PacmanLife::operator bool() const
{
	return life > 0;
}

/**
* @brief return pacman to a start position
* @note
* @retval
*/
void PacmanLife::reset()
{
	life = 3;
}