/**
  *************************************************************************************************************************
  * @file    InteractiveObjEngine.cpp
  * @author  Hridin Andrii
  *          abgridin@gmail.com
  * @date    15-March-2019
  * @brief   Controls dots and fruits objects
  **************************************************************************************************************************
*/
/*includes*/
#include"InteractiveObjEngine.h"
#include"PacDots.h"
#include"Fruit.h"
#include"Help.h"
#include"Tile.h"
#include"Primitives.h"
#include"Dot.h"
#include"DefaultValues.h"

/**
* @brief constructor
* @param1 dots vector
* @param2 renderer pointer
*/
InteractiveObjEngine::InteractiveObjEngine(std::vector<Dot> dots, std::shared_ptr<SDL_Renderer> r):
	Dots(std::make_unique<PacDots>(dots,r)),
	firstfruit(false)
{
	SDL_Rect ShowFruit , MapPosFruit;
	ShowFruit.x = DefaultValues::DisplayFruitX; ShowFruit.y = DefaultValues::DisplayFruitY;
	ShowFruit.w = DefaultValues::DisplayFruitW; ShowFruit.h = DefaultValues::DisplayFruitH;
	MapPosFruit.x = DefaultValues::MapFruitX; MapPosFruit.y = DefaultValues::MapFruitY;
	MapPosFruit.w = DefaultValues::MapFruitW; MapPosFruit.h = DefaultValues::MapFruitH;

	/*create fruits*/
	Fruits = std::move(std::make_unique<Fruit>(MapPosFruit, ShowFruit,
		DefaultValues::FruitImgPath,r));


}

/*Destructor*/
InteractiveObjEngine::~InteractiveObjEngine()
{
}



/**
* @brief run engine
* @note
* @retval
*/
void InteractiveObjEngine::run()
{
	/*after 70 eaten dots generate first fruit. second after 170*/
	switch (dotscnt)
	{
	case 70:
		if (!firstfruit)
		{
			Fruits->GenerateFruit();
			ActiveFtuit = true;
			firstfruit = true;
			start_msecond = SDL_GetTicks();
		}
		break;
	case 170:
		if (!secondfruit)
		{
			Fruits->GenerateFruit();
			ActiveFtuit = true;
			secondfruit = true;
			start_msecond = SDL_GetTicks();
		}
		break;
	}

	if (ActiveFtuit)
	{
		/*9 seconds is given to eat a fruit*/
		if (TimeElapsed(9000, start_msecond))
		{
			Fruits->KillFruit();
			ActiveFtuit = false;
		}
	}
}

/**
* @brief check collision with dots and fruits
* @note
* @param1 pacman rectangle
* @retval ObjectCollisonType
*/
ObjectCollisonType InteractiveObjEngine::CheckCollision(SDL_Rect obj)
{
	ObjectCollisonType ret = Dots->check_collision(obj);
	
	if (dotscnt >= Dots->size())
		return ObjectCollisonType::ALL_DOTS_EATEN;

	switch (ret)
	{
	case ObjectCollisonType::BIG_DOT_EATEN:
		++dotscnt;
		break;
	case ObjectCollisonType::DOT_EATEN:
		++dotscnt;
		break;
	case ObjectCollisonType::NONE_COLLISION:
		if (Fruits->check_collision(obj))
		{
			ret = ObjectCollisonType::FRUIT_EATEN;
			ActiveFtuit = false;
		}
		break;
	}
	return ret;
}

/**
* @brief render all interactive objects
* @note
* @retval
*/
void InteractiveObjEngine::render()
{
	Fruits->render();
	Dots->render();
}

/**
* @brief reset dots and fruit
* @note
* @retval
*/
void InteractiveObjEngine::reset()
{
	ActiveFtuit = false;
	firstfruit = false;
	secondfruit = false;
	Dots->reset();
	Fruits->reset();
	dotscnt = 0;
}